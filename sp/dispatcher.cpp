/* sp/dispatcher.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <limits>

#include "sp/dispatcher.hpp"
#include "log/log.hpp"

typedef Windows::Synch::Locker< Windows::Synch::Mutex > MutexLocker;

Dispatcher::TaskHelper::TaskHelper(DWORD id,
                                   DWORD timeout,
                                   const std::shared_ptr< ITask > &taskRef,
                                   std::function< void (CompletionEvent, DWORD) > completionEventCallback) :
  _id(id),
  _timeout(timeout),
  _sem(0,3),
  _taskRef(taskRef),
  _completionEventCallback(completionEventCallback),
  _timer(_timeout,
    [this] ()
      {
        ::Log::Method m(__LAMBDA_FUNCSIG__("TaskHelper::Timer"),STRING("id = " << _id));

        _completionEventCallback(CompletionEvent::Timeout,_id);
        _sem.release();
        _taskRef->timeoutF();
     })
{
  ::Log::Method(__SIGNATURE__,STRING("id = " << id << ", timeout = " << timeout));
}

Dispatcher::TaskHelper::~TaskHelper()
{
  ::Log::Method(__SIGNATURE__,STRING("id = " << id()));
}

void Dispatcher::TaskHelper::cancel()
{
  ::Log::Method m(__SIGNATURE__,STRING("id = " << id()));

  _completionEventCallback(CompletionEvent::Cancelled,id());
  _sem.release();
  _taskRef->cancelF();
}

void Dispatcher::TaskHelper::run()
{
  ::Log::Method m(__SIGNATURE__,STRING("id = " << id()));

  _thread.reset(new Windows::Thread([this] ()
    {
      ::Log::Method im(__LAMBDA_FUNCSIG__("TaskHelper::run"),STRING("id = " << id()));

      (*_taskRef)(id());
      _completionEventCallback(CompletionEvent::Completed,id());
      _sem.release();
    }));

  _sem.acquire();
}

Dispatcher::Dispatcher() :
  _closing(false),
  _closingSem(0,1),
  _queueSem(0,std::numeric_limits< LONG >::max()),
  _queueThread([this] ()
    {
      ::Log::Method m(__LAMBDA_FUNCSIG__("Dispatcher::queueThread::run"));

      do
      {
        std::shared_ptr< TaskHelper > tH;

        _queueSem.acquire();

        {
          MutexLocker locker(_mutex);

          if (_queueList.empty())
            return;

          DWORD id = _queueList.back();
          _queueList.pop_back();

          Log::Logger() << "selected id = " << id << ", " << _queueList.size() << " pending";

          auto it = _queuedTasks.find(id);
          if (it != _queuedTasks.cend())
          {
            Log::Logger() << "adding " << id << " to running list";
            _runningTasks.insert(id);
            tH = it->second;
          }
        }

        if (tH)
          tH->run();
      }
    #pragma warning(push)
    #pragma warning(disable : 4127)
      while (true);
    #pragma warning(pop)
    })
{
  ::Log::Method(__SIGNATURE__);
}

Dispatcher::~Dispatcher()
{
  ::Log::Method m(__SIGNATURE__);

  {
    MutexLocker locker(_mutex);

    _closing = true;
    _queueSem.release();
  }

  _closingSem.acquire();
}

void Dispatcher::post(DWORD id, DWORD timeout, const std::shared_ptr< ITask > &task)
{
  ::Log::Method m(__SIGNATURE__,STRING("id = " << id << ", timeout = " << timeout));

  {
    MutexLocker locker(_mutex);

    if (_closing)
      return;

    std::shared_ptr< TaskHelper > th = std::make_shared< TaskHelper >(id,timeout,task,
      [this] (TaskHelper::CompletionEvent event, DWORD dwId)
        {
          std::shared_ptr< TaskHelper > sp1, sp2;

          ::Log::Method im(__LAMBDA_FUNCSIG__("Taskhelper::completionChange"),STRING("dwId = " << dwId << ", event = " << event));

          MutexLocker inLocker(_mutex);

          auto it = _queuedTasks.find(dwId);

          if (it != _queuedTasks.cend())
          {
            if ((_runningTasks.find(dwId) != _runningTasks.cend()) &&
                (event != TaskHelper::CompletionEvent::Completed))
            {
              Log::Logger() << "moving " << dwId << " to backup queue";
              _notQueuedTasks.emplace(dwId,it->second);
            }

            Log::Logger() << "removing " << dwId << " from primary queue";
            sp1 = it->second;
            _queuedTasks.erase(it);
          }

          if (event == TaskHelper::CompletionEvent::Completed)
          {
            auto nit = _notQueuedTasks.find(dwId);

            if (nit != _notQueuedTasks.cend())
            {
              Log::Logger() << "removing " << dwId << " from backup queue";
              sp2 = nit->second;
              _notQueuedTasks.erase(nit);
            }

            Log::Logger() << "removing " << dwId << " from running list";
            _runningTasks.erase(dwId);
          }

          if (_closing && _notQueuedTasks.empty() && _queuedTasks.empty())
            _closingSem.release();
        });

    _queueList.push_front(id);
    _queuedTasks.emplace(id,th);
  }

  _queueSem.release();
}

bool Dispatcher::cancel(DWORD id)
{
  ::Log::Method m(__SIGNATURE__,STRING("id = " << id));

  std::shared_ptr< TaskHelper > tH;

  {
    MutexLocker locker(_mutex);

    auto it = _queuedTasks.find(id);
    if (it == _queuedTasks.cend())
      return false;

    tH = it->second;
  }

  tH->cancel();

  return true;
}

std::ostream &operator<<(std::ostream &out, Dispatcher::TaskHelper::CompletionEvent state)
{
  switch (state)
  {
    case Dispatcher::TaskHelper::CompletionEvent::Timeout:
      out << "Timeout";
      break;

    case Dispatcher::TaskHelper::CompletionEvent::Cancelled:
      out << "Cancelled";
      break;

    case Dispatcher::TaskHelper::CompletionEvent::Completed:
      out << "Completed";
      break;

    default:
      break;
  }

  return out;
}

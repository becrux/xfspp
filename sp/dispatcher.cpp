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
        ::Log::Method m(__LAMBDA_FUNCSIG__("TaskHelper::Timer"),LOG_STRING("id = " << _id));

        ::Log::Logger() << "Timer HHHH1" << _id;
        _completionEventCallback(CompletionEvent::Timeout,_id);
        ::Log::Logger() << "Timer HHHH2" << _id;
        _sem.unlock();
        ::Log::Logger() << "Timer HHHH3" << _id;
        _taskRef->timeoutF();
     })
{
  ::Log::Method(__FUNCSIG__,LOG_STRING("id = " << id << ", timeout = " << timeout));
}

Dispatcher::TaskHelper::~TaskHelper()
{
  ::Log::Method(__FUNCSIG__,LOG_STRING("id = " << id()));
}

void Dispatcher::TaskHelper::cancel()
{
  ::Log::Method m(__FUNCSIG__,LOG_STRING("id = " << id()));

  _completionEventCallback(CompletionEvent::Cancelled,id());
  _sem.unlock();
  _taskRef->cancelF();
}

void Dispatcher::TaskHelper::run()
{
  ::Log::Method m(__FUNCSIG__,LOG_STRING("id = " << id()));

  _thread.reset(new Windows::Thread([this] ()
    {
      ::Log::Method m(__LAMBDA_FUNCSIG__("TaskHelper::run"),LOG_STRING("id = " << id()));

      (*_taskRef)(id());
      _completionEventCallback(CompletionEvent::Completed,id());
      _sem.unlock();
    }));

  _sem.lock();
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
        
        _queueSem.lock();
        
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
      while (true);
    })
{
  ::Log::Method(__FUNCSIG__);
}

Dispatcher::~Dispatcher()
{
  ::Log::Method m(__FUNCSIG__);
  
  {
    MutexLocker locker(_mutex);

    _closing = true;
    _queueSem.unlock();
  }

  _closingSem.lock();
}

void Dispatcher::post(DWORD id, DWORD timeout, const std::shared_ptr< ITask > &task)
{
  ::Log::Method m(__FUNCSIG__,LOG_STRING("id = " << id << ", timeout = " << timeout));

  {
    MutexLocker locker(_mutex);

    if (_closing)
      return;

    std::shared_ptr< TaskHelper > th = std::make_shared< TaskHelper >(id,timeout,task,
      [this] (TaskHelper::CompletionEvent event, DWORD id)
        {
          std::shared_ptr< TaskHelper > sp1, sp2;

          ::Log::Method m(__LAMBDA_FUNCSIG__("Taskhelper::completionChange"),LOG_STRING("id = " << id << ", event = " << event));

          MutexLocker inLocker(_mutex);

          auto it = _queuedTasks.find(id);

          if (it != _queuedTasks.cend())
          {
            if ((_runningTasks.find(id) != _runningTasks.cend()) &&
                (event != TaskHelper::CompletionEvent::Completed))
            {
              Log::Logger() << "moving " << id << " to backup queue";
              _notQueuedTasks.emplace(id,it->second);
            }

            Log::Logger() << "removing " << id << " from primary queue";
            sp1 = it->second;
            _queuedTasks.erase(it);
          }

          if (event == TaskHelper::CompletionEvent::Completed)
          {
            auto it = _notQueuedTasks.find(id);

            if (it != _notQueuedTasks.cend())
            {
              Log::Logger() << "removing " << id << " from backup queue";
              sp2 = it->second;
              _notQueuedTasks.erase(it);
            }

            Log::Logger() << "removing " << id << " from running list";
            _runningTasks.erase(id);
          }

          if (_closing && _notQueuedTasks.empty() && _queuedTasks.empty())
            _closingSem.unlock();
        });

    _queueList.push_front(id);
    _queuedTasks.emplace(id,th);
  }

  _queueSem.unlock();
}

bool Dispatcher::cancel(DWORD id)
{
  ::Log::Method m(__FUNCSIG__,LOG_STRING("id = " << id));

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
  }

  return out;
}

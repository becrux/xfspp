#include <iostream>
#include <limits>

#include "sp/dispatcher.hpp"

typedef Windows::Synch::Locker< Windows::Synch::Mutex > MutexLocker;

Dispatcher::TaskHelper::TaskHelper(DWORD id,
                                   DWORD timeout,
                                   const std::shared_ptr< ITask > &taskRef,
                                   std::function< void (CompletionState, DWORD) > stateChange) :
  _id(id),
  _timeout(timeout),
  _sem(0,1),
  _taskRef(taskRef),
  _stateChange(stateChange),
  _timer(_timeout,
    [this] ()
      {
        _stateChange((_thread)? CompletionState::TimeoutWhileRunning : CompletionState::Timeout,_id);
        _sem.unlock();
        _taskRef->timeoutF();
     })
{

}

void Dispatcher::TaskHelper::cancel()
{
  _stateChange((_thread)? CompletionState::CancelledWhileRunning : CompletionState::Cancelled,id());
  _sem.unlock();
  taskRef()->cancelF();
}

void Dispatcher::TaskHelper::run()
{
  std::cout << "running " << id() << std::endl;

  _thread = std::unique_ptr< Windows::Thread >(new Windows::Thread([this] ()
    {
      (*taskRef())(_id);
      _stateChange(CompletionState::Completed,id());
      _sem.unlock();
    }));

  _sem.lock();
}

Dispatcher::Dispatcher() :
  _closing(false),
  _queueSem(0,std::numeric_limits< LONG >::max()),
  _queueThread([this] ()
    {
      do
      {
        std::shared_ptr< TaskHelper > tH;
        
        _queueSem.lock();
        
        {
          MutexLocker locker(_mutex);
        
          if (_queueList.empty() && _closing)
            return;
        
          DWORD id = _queueList.back();
          _queueList.pop_back();
            
          auto it = _queuedTasks.find(id);
          if (it != _queuedTasks.cend())
            tH = it->second;
        }
        
        if (tH)
          tH->run();
      }
      while (true);
    })
{
  std::cout << "Dispatcher::Dispatcher" << std::endl;
}

Dispatcher::~Dispatcher()
{
  std::cout << "Dispatcher::~Dispatcher begin" << std::endl;
  
  {
    MutexLocker locker(_mutex);

    _closing = true;
    _queueSem.unlock();
  }

  std::cout << "Dispatcher::~Dispatcher end" << std::endl;
}

void Dispatcher::post(DWORD id, DWORD timeout, const std::shared_ptr< ITask > &task)
{
  {
    MutexLocker locker(_mutex);

    std::shared_ptr< TaskHelper > th = std::make_shared< TaskHelper >(id,timeout,task,
      [this] (TaskHelper::CompletionState state, DWORD id)
        {
          MutexLocker inLocker(_mutex);

          std::cout << id << ", state = " << static_cast< int >(state) << std::endl;

          auto it = _queuedTasks.find(id);

          if (it != _queuedTasks.cend())
          {
            if ((state == TaskHelper::CompletionState::TimeoutWhileRunning) ||
                (state == TaskHelper::CompletionState::CancelledWhileRunning))
              _notQueuedTasks.emplace(id,it->second);

            _queuedTasks.erase(it);
          }

          if (state == TaskHelper::CompletionState::Completed)
          {
            auto it = _notQueuedTasks.find(id);

            if (it != _notQueuedTasks.cend())
              _notQueuedTasks.erase(it);
          }
        });

    _queueList.push_front(id);
    _queuedTasks.emplace(id,th);
  }

  _queueSem.unlock();
}

bool Dispatcher::cancel(DWORD id)
{
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

std::shared_ptr< Dispatcher > Dispatcher::create()
{
  return std::shared_ptr< Dispatcher >(new Dispatcher());
}

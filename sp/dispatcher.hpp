#pragma once
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include <memory>
#include <map>
#include <list>

#include <windows.h>

#include "sp/task.hpp"
#include "win32/synch.hpp"
#include "win32/thread.hpp"
#include "win32/timer.hpp"

class Dispatcher : public std::enable_shared_from_this< Dispatcher >
{
  class TaskHelper
  {
  public:
    enum class CompletionState { Timeout, Cancelled, TimeoutWhileRunning, CancelledWhileRunning, Completed };

  private:
    DWORD _id;
    DWORD _timeout;
    Windows::Synch::Semaphore _sem;
    std::shared_ptr< ITask > _taskRef;
    std::function< void (CompletionState, DWORD) > _stateChange;
    Windows::Timer _timer;
    std::unique_ptr< Windows::Thread > _thread;

  public:
    explicit TaskHelper(DWORD id,
                        DWORD timeout,
                        const std::shared_ptr< ITask > &taskRef,
                        std::function< void (CompletionState, DWORD) > stateChange);

    std::shared_ptr< ITask > taskRef() const { return _taskRef; }

    DWORD id() const { return _id; }

    void cancel();
    void expire();
    void run();
  };

  bool _closing;
  Windows::Synch::Mutex _mutex;
  std::list< DWORD > _queueList;
  std::map< DWORD,std::shared_ptr< TaskHelper > > _notQueuedTasks;
  std::map< DWORD,std::shared_ptr< TaskHelper > > _queuedTasks;
  Windows::Synch::Semaphore _queueSem;
  Windows::Thread _queueThread;

  explicit Dispatcher();

public:
  ~Dispatcher();

  void post(DWORD id, DWORD timeout, const std::shared_ptr< ITask > &task);
  bool cancel(DWORD id);

  static std::shared_ptr< Dispatcher > create();
};

#endif

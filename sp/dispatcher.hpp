/* sp/dispatcher.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include <memory>
#include <map>
#include <list>
#include <set>

#include "sp/task.hpp"
#include "win32/synch.hpp"
#include "win32/thread.hpp"
#include "win32/timer.hpp"
#include "util/constraints.hpp"

class Dispatcher
{
  class TaskHelper
  {
  public:
    enum class CompletionEvent { Timeout, Cancelled, Completed };

  private:
    DWORD _id;
    DWORD _timeout;
    Windows::Synch::Semaphore _sem;
    std::shared_ptr< ITask > _taskRef;
    std::function< void (CompletionEvent, DWORD) > _completionEventCallback;
    Windows::Timer _timer;
    std::unique_ptr< Windows::Thread > _thread;

    NON_COPYABLE(TaskHelper);

  public:
    explicit TaskHelper(DWORD id,
                        DWORD timeout,
                        const std::shared_ptr< ITask > &taskRef,
                        std::function< void (CompletionEvent, DWORD) > completionEventCallback);
    ~TaskHelper();

    DWORD id() const { return _id; }

    void cancel();
    void expire();
    void run();
  };

  bool _closing;
  Windows::Synch::Semaphore _closingSem;
  Windows::Synch::Mutex _mutex;
  std::list< DWORD > _queueList;
  std::set< DWORD > _runningTasks;
  std::map< DWORD,std::shared_ptr< TaskHelper > > _queuedTasks;
  std::map< DWORD,std::shared_ptr< TaskHelper > > _notQueuedTasks;
  Windows::Synch::Semaphore _queueSem;
  Windows::Thread _queueThread;

  NON_COPYABLE(Dispatcher);

public:
  explicit Dispatcher();
  ~Dispatcher();

  void post(DWORD id, DWORD timeout, const std::shared_ptr< ITask > &task);
  bool cancel(DWORD id);

  friend std::ostream &operator<<(std::ostream &out, TaskHelper::CompletionEvent state);
};

std::ostream &operator<<(std::ostream &out, Dispatcher::TaskHelper::CompletionEvent state);

#endif

/* sp/task.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <windows.h>

#include <functional>

#include "util/constraints.hpp"

class ITask
{
  NON_COPYABLE(ITask);
  NON_MOVEABLE(ITask);

public:
  ITask() { }
  virtual ~ITask() { }

  virtual void operator()(DWORD id) = 0;

  virtual void timeoutF() = 0;
  virtual void cancelF() = 0;
};

class LambdaTask : public ITask
{
  DWORD _i;
  std::function< void (DWORD) > _f;

  NON_COPYABLE(LambdaTask);

public:
  explicit LambdaTask(DWORD i, std::function< void (DWORD) > f);
  ~LambdaTask();

  void operator()(DWORD id);

  void timeoutF();
  void cancelF();
};

#endif

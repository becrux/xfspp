#pragma once
#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <windows.h>

#include <functional>

class ITask
{
  ITask(const ITask &);
  ITask &operator=(const ITask &);

  ITask(ITask &&);
  ITask &operator=(ITask &&);

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

public:
  explicit LambdaTask(DWORD i, std::function< void (DWORD) > f);
  ~LambdaTask();

  void operator()(DWORD id);

  void timeoutF();
  void cancelF();
};

#endif

#include <iostream>

#include "sp/task.hpp"

LambdaTask::LambdaTask(DWORD i, std::function< void (DWORD) > f) : _i(i), _f(f)
{
  std::cout << "LambdaTask::LambdaTask " << _i << std::endl;
}

LambdaTask::~LambdaTask()
{
  std::cout << "LambdaTask::~LambdaTask " << _i << std::endl;
}

void LambdaTask::operator()(DWORD id)
{
  std::cout << "LambdaTask::operator() " << _i << " begin" << std::endl;
  _f(id);
  std::cout << "LambdaTask::operator() " << _i << " end" << std::endl;
}

void LambdaTask::timeoutF()
{
  std::cout << "LambdaTask::timeoutF() " << _i << std::endl;
}

void LambdaTask::cancelF()
{
  std::cout << "LambdaTask::cancelF() " << _i << std::endl;
}

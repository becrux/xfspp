#include <iostream>
#include <fstream>

#include <windows.h>

#include "win32/synch.hpp"
#include "win32/thread.hpp"
#include "win32/timer.hpp"
#include "sp/task.hpp"
#include "sp/dispatcher.hpp"
#include "log/log.hpp"

int main(int argc, char **argv)
{
  Dispatcher d;
      
  for (DWORD i = 0; i < 10; ++i)
    d.post(i,2000,std::make_shared< LambdaTask >(
      i,
      [i] (DWORD id)
        {
          Log::Logger() << "RUNNING " << i;
          Sleep((i + 1) * 1000);
        }));

	return 0;
}

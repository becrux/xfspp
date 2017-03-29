#include <iostream>

#include <windows.h>

#include "win32/synch.hpp"
#include "sp/task.hpp"
#include "sp/dispatcher.hpp"

int main(int argc, char **argv)
{
  {
    std::shared_ptr< Dispatcher > d = Dispatcher::create();
    
    for (DWORD i = 0; i < 10; ++i)
      d->post(i,2000,std::make_shared< LambdaTask >(
        i,
        [i] (DWORD id)
          {
            std::cout << i << std::endl;
            Sleep((i + 1) * 1000);
          }));
  }

	return 0;
}

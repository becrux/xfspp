#include <windows.h>

#include "sp/task.hpp"
#include "sp/dispatcher.hpp"
#include "log/log.hpp"

int main(int, char **)
{
  Dispatcher d;
      
  for (DWORD i = 0; i < 10; ++i)
    d.post(i,2000,std::make_shared< LambdaTask >(
      i,
      [i] (DWORD)
        {
          Log::Logger() << "RUNNING " << i;
          Sleep((i + 1) * 1000);
        }));

	return 0;
}

#include "gtest/gtest.h"
#include "win32/library.hpp"
#include "util/methodscope.hpp"

static Windows::Library *lib = nullptr;

TEST(MgrLoader, NoParam)
{ 
  EXPECT_TRUE(true);
}

int main(int argc, char **argv)
{
  lib = new Windows::Library(L"msxfs.dll");
  MethodScope libScope([] () { delete lib; });
  
  ::testing::InitGoogleTest(&argc,argv);

  return RUN_ALL_TESTS();
}

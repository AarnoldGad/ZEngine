#include <zengine/zengine.hpp>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <cassert>

#include <Time/TimeTest.h>

void foo(int n)
{
   std::cout << "Received " << n << std::endl;
}

void foo2(int n)
{
   return 0;
}

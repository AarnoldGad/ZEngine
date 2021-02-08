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
   std::cout << "Received2 " << n << std::endl;
}

int main()
{
   ze::Signal<void(int)> sig;
   ze::Connection<void(int)> connection(&sig, &foo);
   ze::Connection<void(int)> connection2(&sig, &foo2);
   sig.emit(6);
   return 0;
}

#include <zengine/zengine.hpp>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <cassert>

#include <Time/TimeTest.h>

class Resource
{
public:

   void load(int n)
   {
      n | tee;
   }
};

int main()
{
   ze::ResourceManager<Resource>::load("foo", 1);
   ze::ResourceManager<Resource>::load("bar", 2);
   auto result = ze::ResourceManager<Resource>::find("bar"); // shared_ptr to "bar"

   ze::ResourceManager<Resource>::release("foo");
   ze::ResourceManager<Resource>::releaseAll();
   result = ze::ResourceManager<Resource>::find("bar"); // Null
   return 0;
}

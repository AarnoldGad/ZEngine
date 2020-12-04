#include <zengine/zengine.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <ctime>
#include <Windows.h>
#include <zengine/Experimental/tee.hpp>

int main()
{
   ze::Logger logger(std::cout);
   logger.info() << ze::Logger::warn << "Hello";
   std::ofstream file("tee");
   stee(45, file);

   return 0;
}

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

int main()
{
   ze::Logger logger(std::cout);
   std::string foo = "example";
   logger.logFormatedLine(ze::ZLogger<char>::Info, "Effective {1} with great {1} {2} Number {3}", "test", foo, -76);

   return 0;
}

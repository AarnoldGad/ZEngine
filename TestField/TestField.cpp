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

#include <zengine/zengine.hpp>

class Event
{
public:

   virtual void bar() {}

   template<typename From>
   void foo(Event& event)
   {
      From* a = dynamic_cast<From*>(&event);
      if (a == nullptr)
         std::cout << "Not castable" << std::endl;
      else
         std::cout << "Castable" << std::endl;
   }
};

class KeyEvent : public Event
{

};

class MouseEvent : public Event
{

};

class MouseButtonPressed : public MouseEvent
{

};

class MouseButtonReleased : public MouseEvent
{

};


int main()
{
   MouseButtonPressed a;
   Event& b = a;
   a.foo<Event>(b);
   return 0;
}

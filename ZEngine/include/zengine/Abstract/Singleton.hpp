/**
 * Singleton.hpp
 * 18 Nov 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_SINGLETON
#define ZE_SINGLETON

namespace ze
{
   template<typename ObjectType>
   class Singleton
   {
   public:
      static ObjectType& Instance();
      static void Reset();

   protected:
      Singleton() = default;
      virtual ~Singleton() = default;

   private:
      Singleton(Singleton const&) = delete;
      Singleton& operator=(Singleton const&) = delete;
      Singleton(Singleton&&) = delete;
      Singleton& operator=(Singleton&&) = delete;

      static std::unique_ptr<ObjectType> s_instance;
   };
}

#include <inline/Abstract/Singleton.inl>

#endif // ZE_SINGLETON

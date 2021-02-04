/**
 * Time.hpp
 * 18 Dec 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
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
#ifndef ZE_TIME
#define ZE_TIME

#include <zebuild.hpp>

namespace ze
{
   class ZE_API Time
   {
   public:
      static Time const Null;

      static Time Now() noexcept;
      static Time Seconds(float seconds) noexcept;
      static Time Milliseconds(int milliseconds) noexcept;
      static Time Microseconds(int64_t microseconds) noexcept;

      float asSeconds() const noexcept;
      int asSecondsInt() const noexcept;
      int32_t asMilliseconds() const noexcept;
      int64_t asMicroseconds() const noexcept;

      Time(int64_t microseconds);
      Time();

      Time operator-() const noexcept;

      Time& operator+=(Time const& other) noexcept;

      Time& operator-=(Time const& other) noexcept;

      Time& operator*=(float factor) noexcept;
      Time& operator*=(int64_t factor) noexcept;

      Time& operator/=(float factor);
      Time& operator/=(int64_t factor);

      Time& operator%=(Time const& mod) noexcept;

      bool operator==(Time const& other) const noexcept;
      bool operator!=(Time const& other) const noexcept;
      bool operator<=(Time const& other) const noexcept;
      bool operator>=(Time const& other) const noexcept;
      bool operator<(Time const& other) const noexcept;
      bool operator>(Time const& other) const noexcept;

      Time operator+(Time const& other) const noexcept;

      Time operator-(Time const& other) const noexcept;

      Time operator*(float factor) const noexcept;
      Time operator*(int64_t factor) const noexcept;

      Time operator/(Time const& other) const;
      Time operator/(float factor) const;
      Time operator/(int64_t factor) const;

      Time operator%(Time const& other) const noexcept;

   private:
      int64_t m_microseconds;
   };
}

#include <inline/Common/Time/Time.inl>

#endif // ZE_TIME

/**
 * Signal.hpp
 * 6 Feb 2021
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
#ifndef ZE_SIGNAL
#define ZE_SIGNAL

#include <zebuild.hpp>
#include <functional>

#include <zengine/Common/Signal/Connection.hpp>

namespace ze
{
   template<typename... FnSignature>
   class Signal;

   template<typename ReturnType, typename... Args>
   class Signal<ReturnType(Args...)>
   {
   public:
      using ConnectionType = typename ze::Connection<ReturnType(Args...)>;
      using ReceiverType = typename std::function<ReturnType(Args...)>;

      ConnectionType connect(ReceiverType receiver) noexcept;
      void connect(ConnectionType& connection) noexcept;
      void disconnect(ConnectionType& connection) noexcept;
      void clearConnections() noexcept;

      void emit(Args&&... args);

      Signal() noexcept;
      ~Signal() noexcept;

      Signal(Signal const&) = delete;
      Signal(Signal&&) = delete;
      Signal& operator=(Signal const&) = delete;
      Signal& operator=(Signal&&) = delete;

   private:
      void replaceConnection(ConnectionType& oldConnection, ConnectionType& newConnection) noexcept;

      std::list<ConnectionType*> m_connections;

      friend class ConnectionType;
   };
}

#include <inline/Common/Signal/Signal.inl>

#endif // ZE_SIGNAL

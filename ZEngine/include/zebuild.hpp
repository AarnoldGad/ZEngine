#ifndef ZE_BUILD
#define ZE_BUILD

   #if defined(_WIN32)

      #define ZE_BUILD_WINDOWS

      #if defined(_MSC_VER)
         #pragma warning(disable: 4251)
      #endif

      #if defined(_WINDLL)
         #define ZE_DLLEXPORT
      #endif

   #elif defined(__APPLE__) || defined(__MACH__)
      #define ZE_BUILD_APPLE
   #elif defined(__unix__)
      #define ZE_BUILD_LINUX
   #else
      #error Platform not supported
   #endif

   #if defined(ZE_BUILD_WINDOWS)
      #if defined(ZE_DLLEXPORT)
         #define ZE_API __declspec(dllexport)
      #else
         #define ZE_API __declspec(dllimport)
      #endif
   #elif __GNUC__ >= 4
      #define ZE_API __attribute__ ((__visibility__("default")))
   #else
      #define ZE_API
   #endif

#include "constants.hpp"

#endif // ZE_BUILD

#ifndef ZE_SINGLETON
#define ZE_SINGLETON

// Unique or Raw ptr ?
#include <memory>

template<typename Object>
class Singleton
{
public:
   static Object& Instance();
   static void Reset();

protected:
   Singleton() = default;
   ~Singleton() = default;

private:
   Singleton(Singleton const&) = delete;
   Singleton& operator=(Singleton const&) = delete;

   static std::unique_ptr<Object> s_instance;
};

#include <zengine/Abstract/Singleton.inl>

#endif // ZE_SINGLETON

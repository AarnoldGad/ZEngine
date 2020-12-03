template<typename Object>
std::unique_ptr<Object> Singleton<Object>::s_instance = nullptr;

template<typename Object>
Object& Singleton<Object>::Instance()
{
   if (s_instance)
      s_instance = std::make_unique<Object>();

   return *s_instance;
}

template<typename Object>
void Singleton<Object>::Reset()
{
   s_instance.reset(nullptr);
}
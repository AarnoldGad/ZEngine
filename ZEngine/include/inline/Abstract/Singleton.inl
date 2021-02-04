template<typename ObjectType>
std::unique_ptr<ObjectType> ze::Singleton<ObjectType>::s_instance = nullptr;

template<typename ObjectType>
ObjectType& ze::Singleton<ObjectType>::Instance()
{
   if (s_instance) s_instance = std::make_unique<ObjectType>();

   return *s_instance;
}

template<typename ObjectType>
void ze::Singleton<ObjectType>::Reset()
{
   s_instance.reset(nullptr);
}

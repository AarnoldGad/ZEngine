template<typename ResourceType>
std::unordered_map<std::string, std::shared_ptr<ResourceType> > ze::ResourceManager<ResourceType>::m_resources{};

template<typename ResourceType>
template<typename... Args>
std::shared_ptr<ResourceType> ze::ResourceManager<ResourceType>::load(std::string&& id, Args&&... args)
{
   auto result = m_resources.try_emplace(std::move(id), std::make_shared<ResourceType>()); // TODO Exception Safe

   ResourcePtr resource = result.first->second;
   resource->load(std::forward<Args>(args)...); // TODO Exception Safe

   return resource;
}

template<typename ResourceType>
std::shared_ptr<ResourceType> ze::ResourceManager<ResourceType>::find(std::string const& id) noexcept
{
   auto resource = m_resources.find(id);
   return resource != m_resources.end() ? resource->second : nullptr;
}

template<typename ResourceType>
std::shared_ptr<ResourceType> ze::ResourceManager<ResourceType>::release(std::string const& id) noexcept
{
   return m_resources.extract(id).mapped();
}

template<typename ResourceType>
void ze::ResourceManager<ResourceType>::releaseAll() noexcept
{
   m_resources.clear();
}

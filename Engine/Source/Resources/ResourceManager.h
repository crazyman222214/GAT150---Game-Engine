#pragma once
#include "Resource.h"
#include "../Core/Singleton.h"
#include <map>
#include <iostream>

class ResourceManager : public Singleton<ResourceManager>
{
public:
	template <typename T, typename ... TArgs>
	res_t<T> Get(const std::string& name, TArgs ... args);

	friend class Singleton;
private:
	std::map<std::string, res_t<Resource>> m_resources;
};

template<typename T, typename ... TArgs>
inline res_t<T> ResourceManager::Get(const std::string& name, TArgs ... args)
{
	//Find resource in resource manager
	if (m_resources.find(name) != m_resources.end())
	{
		return std::dynamic_pointer_cast<T>(m_resources[name]);
	}
	
	res_t<T> resource = std::make_shared<T>();
	if (!resource->Create(name, args...))
	{
		std::cerr << "Could not create resource: " << name << std::endl;
		return res_t<T>();
	}

	m_resources[name] = resource;
	return resource;

}

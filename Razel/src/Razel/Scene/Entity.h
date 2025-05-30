#pragma once
#include "Scene.h"
#include "entt.hpp"

namespace Razel
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T,typename...Args>
		T& AddComponent(Args&&...args) 
		{
			RZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;

		}
		template<typename T>
		T& GetComponent()
		{
			RZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}
		template<typename T>
		void RemoveComponent()
		{
			RZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}


		operator bool()const
		{
			return m_EntityHandle != entt::null;
		}
		operator entt::entity()const { return m_EntityHandle; }
		operator uint32_t()const 
		{
			return (uint32_t)m_EntityHandle;
		}
		bool operator==(const Entity& other) const
		{
			return m_Scene == other.m_Scene && m_EntityHandle == other.m_EntityHandle;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		Scene* m_Scene = nullptr;
		entt::entity m_EntityHandle = entt::null;
	};
}


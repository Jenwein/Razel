#pragma once

#include "Razel/Core/Timestep.h"

#include "Razel/Renderer/EditorCamera.h"
#include "entt.hpp"

namespace Razel
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts,EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		// 获取主相机实体
		Entity GetPrimaryCameraEntity();

		entt::registry m_Registry;

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}

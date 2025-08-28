#pragma once

#include "Razel/Core/Timestep.h"

#include "Razel/Renderer/EditorCamera.h"
#include "entt.hpp"

namespace Razel
{
	struct PhysicsWorldSettings
	{
		glm::vec2 Gravity = { 0.0f, -9.8f };	// 重力
		float RestitutionThreshold = 0.5f;		// 恢复阈值(触发弹力的阈值) 
	};

	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts,EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		// 获取主相机实体
		Entity GetPrimaryCameraEntity();

		PhysicsWorldSettings m_PhysicsWorldSettings;

		entt::registry m_Registry;

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		uint32_t m_PhysicsWorldId;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}

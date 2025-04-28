#pragma once

#include "Razel/Core/Base.h"
#include "Razel/Core/Log.h"
#include "Razel/Scene/Scene.h"
#include "Razel/Scene/Entity.h"

namespace Razel
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);
		void SetContext(const Ref<Scene>& scene);
		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}


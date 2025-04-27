#include "SceneHierarchyPanel.h"

#include "Razel/Scene/Components.h"

#include <imgui/imgui.h>
namespace Razel
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_Context = scene;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		m_Context->m_Registry.view<entt::entity>().each([&](auto entityID) {
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);
		});

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		//ImGuiTreeNodeFlags flags= ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	}

}
#include "rzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Razel/Application.h"


namespace Razel
{
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;	// 启用鼠标光标支持，使 UI 可以更改鼠标指针形状
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;	// 启用鼠标位置设置，允许 ImGui 代码更改鼠标位置。

		// TEMPORARY: should eventually use Hazel key codes
		// c将 ImGui 的键值 映射到 GLFW 的键值
		Application& app = Application::Get();
		glfwSetKeyCallback((GLFWwindow*)&app.GetWindow(), KeyCallback);

		// 将 ImGui 的键值 映射到 GLFW 的键值
		ImGui_ImplOpenGL3_Init("#version 410");


	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f, 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGuiLayer::OnEvent(Event& event)
	{

	}
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		ImGuiIO& io = ImGui::GetIO();
		bool is_pressed = (action != GLFW_RELEASE);  // 按下 = true，释放 = false
		io.AddKeyEvent(ImGuiKey_Tab, key == GLFW_KEY_TAB && is_pressed);
		io.AddKeyEvent(ImGuiKey_LeftArrow, key == GLFW_KEY_LEFT && is_pressed);
		io.AddKeyEvent(ImGuiKey_RightArrow, key == GLFW_KEY_RIGHT && is_pressed);
		io.AddKeyEvent(ImGuiKey_UpArrow, key == GLFW_KEY_UP && is_pressed);
		io.AddKeyEvent(ImGuiKey_DownArrow, key == GLFW_KEY_DOWN && is_pressed);
		io.AddKeyEvent(ImGuiKey_PageUp, key == GLFW_KEY_PAGE_UP && is_pressed);
		io.AddKeyEvent(ImGuiKey_PageDown, key == GLFW_KEY_PAGE_DOWN && is_pressed);
		io.AddKeyEvent(ImGuiKey_Home, key == GLFW_KEY_HOME && is_pressed);
		io.AddKeyEvent(ImGuiKey_End, key == GLFW_KEY_END && is_pressed);
		io.AddKeyEvent(ImGuiKey_Insert, key == GLFW_KEY_INSERT && is_pressed);
		io.AddKeyEvent(ImGuiKey_Delete, key == GLFW_KEY_DELETE && is_pressed);
		io.AddKeyEvent(ImGuiKey_Backspace, key == GLFW_KEY_BACKSPACE && is_pressed);
		io.AddKeyEvent(ImGuiKey_Space, key == GLFW_KEY_SPACE && is_pressed);
		io.AddKeyEvent(ImGuiKey_Enter, key == GLFW_KEY_ENTER && is_pressed);
		io.AddKeyEvent(ImGuiKey_Escape, key == GLFW_KEY_ESCAPE && is_pressed);
		io.AddKeyEvent(ImGuiKey_A, key == GLFW_KEY_A && is_pressed);
		io.AddKeyEvent(ImGuiKey_C, key == GLFW_KEY_C && is_pressed);
		io.AddKeyEvent(ImGuiKey_V, key == GLFW_KEY_V && is_pressed);
		io.AddKeyEvent(ImGuiKey_X, key == GLFW_KEY_X && is_pressed);
		io.AddKeyEvent(ImGuiKey_Y, key == GLFW_KEY_Y && is_pressed);
		io.AddKeyEvent(ImGuiKey_Z, key == GLFW_KEY_Z && is_pressed);
	}
}
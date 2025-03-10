#include "rzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Razel/Application.h"

//TEMPORARY
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Razel
{

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
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;	// ���������֧�֣�ʹ UI ���Ը������ָ����״
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;	// �������λ�����ã����� ImGui ����������λ�á�
		




		// TEMPORARY: should eventually use Hazel key codes
		Application& app = Application::Get();

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
			
		float time = (float)glfwGetTime();								// ��ǰʱ��
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);	// ��ǰ֡����һ֮֡���ʱ����
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
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		// �� ImGuiIO �ж�Ӧ��갴����״̬����Ϊ true������ ImGui �ð����ѱ�����
		//io.MouseDown[e.GetMouseButton()] = true;
		io.AddMouseButtonEvent(e.GetMouseButton(), true);
		
		// ���¼����Ա��������������
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		//io.MouseDown[e.GetMouseButton()] = false;
		io.AddMouseButtonEvent(e.GetMouseButton(), false);

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		//io.MousePos = ImVec2(e.GetX(), e.GetY());
		io.AddMousePosEvent(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		//io.MouseWheelH += e.GetXOffset();
		//io.MouseWheel += e.GetYOffset();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		// ��GLFW����ӳ�䵽ImGui����
		//ImGuiKey key = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode());

		// ʹ���µ� AddKeyEvent ��¼����״̬
		io.AddKeyEvent((ImGuiKey)e.GetKeyCode(), true);

		// ��¼���μ�״̬��Ctrl, Shift, Alt, Super��
		io.AddKeyEvent(ImGuiKey_ModCtrl, e.GetKeyCode() == GLFW_KEY_LEFT_CONTROL || e.GetKeyCode() == GLFW_KEY_RIGHT_CONTROL);
		io.AddKeyEvent(ImGuiKey_ModShift, e.GetKeyCode() == GLFW_KEY_LEFT_SHIFT || e.GetKeyCode() == GLFW_KEY_RIGHT_SHIFT);
		io.AddKeyEvent(ImGuiKey_ModAlt, e.GetKeyCode() == GLFW_KEY_LEFT_ALT || e.GetKeyCode() == GLFW_KEY_RIGHT_ALT);
		io.AddKeyEvent(ImGuiKey_ModSuper, e.GetKeyCode() == GLFW_KEY_LEFT_SUPER || e.GetKeyCode() == GLFW_KEY_RIGHT_SUPER);

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent((ImGuiKey)e.GetKeyCode(), false);

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
		{
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;

	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		//TEMPRORY
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;

	}

}
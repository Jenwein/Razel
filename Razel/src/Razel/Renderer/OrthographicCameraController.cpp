#include "rzpch.h"

#include "Razel/Renderer/OrthographicCameraController.h"

#include "Razel/Core/Input.h"
#include "Razel/Core/KeyCodes.h"

namespace Razel
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation /*= false*/)
		:m_AspectRatio(aspectRatio),m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		RZ_PROFILE_FUNCTION();

		if (Razel::Input::IsKeyPressed(RZ_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Razel::Input::IsKeyPressed(RZ_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Razel::Input::IsKeyPressed(RZ_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Razel::Input::IsKeyPressed(RZ_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Razel::Input::IsKeyPressed(RZ_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Razel::Input::IsKeyPressed(RZ_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		m_Camera.SetPosition(m_CameraPosition);		// �������λ��
		m_Camera.SetRotation(m_CameraRotation);		// ���������ת
		m_CameraTranslationSpeed = m_ZoomLevel;		// ����ƶ��ٶ������ż���仯
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		RZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		RZ_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		RZ_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
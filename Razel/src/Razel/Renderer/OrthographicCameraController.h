#pragma once
#include "Razel/Renderer/OrthographicCamera.h"
#include "Razel/Core/Timestep.h"


#include "Razel/Events/ApplicationEvent.h"
#include "Razel/Events/MouseEvent.h"

namespace Razel
{
	// �������������
	class OrthographicCameraController
	{
	public:
		// aspectRadio-����Ŀ�߱� ,rotation-�Ƿ�������ת
		OrthographicCameraController(float aspectRatio, bool rotation = true);

		// ���������Transform
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);

		// ��ȡ�������
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera()const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;								// ����Ŀ�߱�
		float m_ZoomLevel = 1.0f;							// ���ż���
		OrthographicCamera m_Camera;						// �������

		bool m_Rotation;									// �Ƿ�������ת

		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };	// ���λ��
		float m_CameraRotation = 0.0f;						// �����ת�Ƕ�
		
		// ���λ���ٶ�,�����ת�ٶ�
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;	
	};
}


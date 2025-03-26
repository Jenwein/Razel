#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Core/Timestep.h"
#include "Events/Event.h"

namespace Razel
{
	// �������������
	class OrthographicCameraController
	{
	public:
		// aspectRadio-����Ŀ�߱� ,rotation-�Ƿ�������ת
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		// ���������Transform
		void OnUpdate(Timestep);

		void OnEvent(Event& e);

		// ��ȡ�������
		OrthographicCamera& GetCamera();
		const OrthographicCamera& GetCamera()const;

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


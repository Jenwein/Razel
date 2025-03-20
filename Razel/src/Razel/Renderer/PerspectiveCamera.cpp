#include "rzpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Razel
{
	PerspectiveCamera::PerspectiveCamera(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	// �����������ͼ�������ͼͶӰ����
	void PerspectiveCamera::RecalculateViewMatrix()
	{
		// �任����
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), m_Position) *								// ƽ�ƾ���
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));	// ��ת����ת�ľ�����ת�ĽǶȣ���ת��(Z)��

		m_ViewMatrix = glm::inverse(transform);		// �ƶ�����������������ȡ��
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
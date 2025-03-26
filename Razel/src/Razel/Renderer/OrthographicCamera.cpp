#include "rzpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Razel
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	// 更新相机的视图矩阵和视图投影矩阵
	void OrthographicCamera::RecalculateViewMatrix()
	{
		// 变换矩阵
		glm::mat4 transform = 
			glm::translate(glm::mat4(1.0f), m_Position) *								// 平移矩阵
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));	// 旋转（旋转的矩阵，旋转的角度，旋转轴(Z)）
		
		m_ViewMatrix = glm::inverse(transform);		// 移动场景到反方向所以取逆
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
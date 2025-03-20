#pragma once
#include <glm/glm.hpp>
namespace Razel
{
	// 正交投影相机
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition()const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation()const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetPositionMatrix()const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix()const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix()const { return m_ViewProjectionMatrix; }

	private:
		//重新计算视图矩阵和视图投影矩阵
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);			// 投影矩阵
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);					// 视图矩阵
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);		// 视图投影矩阵

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };	// 相机位置
		float m_Rotation = 0.0f;					// 相机旋转角度（绕Z轴）
	};
}

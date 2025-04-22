#pragma once
#include "Razel/Renderer/OrthographicCamera.h"
#include "Razel/Core/Timestep.h"


#include "Razel/Events/ApplicationEvent.h"
#include "Razel/Events/MouseEvent.h"

namespace Razel
{
	// 正交相机控制类
	class OrthographicCameraController
	{
	public:
		// aspectRadio-相机的宽高比 ,rotation-是否启用旋转
		OrthographicCameraController(float aspectRatio, bool rotation = true);

		// 更新相机的Transform
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);

		// 获取相机对象
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera()const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;								// 相机的宽高比
		float m_ZoomLevel = 1.0f;							// 缩放级别
		OrthographicCamera m_Camera;						// 正交相机

		bool m_Rotation;									// 是否启用旋转

		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };	// 相机位置
		float m_CameraRotation = 0.0f;						// 相机旋转角度
		
		// 相机位移速度,相机旋转速度
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;	
	};
}


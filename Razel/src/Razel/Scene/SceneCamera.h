#pragma once
#include "Razel/Renderer/Camera.h"

namespace Razel
{
    class SceneCamera :public Camera
    {
    public:
        enum class ProjectionType { Perspective = 0, Orthographic = 1 };
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        // 设置 正交/透视 投影参数
        void SetOrthographic(float size, float nearClip, float farClip);
        void SetPerspective(float verticalFOV, float nearClip, float farClip);

        // 设置视口尺寸
        void SetViewportSize(uint32_t width, uint32_t height);
        
        // 透视投影
        float GetPerspectiveVerticalFOV()const { return m_PerspectiveFOV; }
        void SetPerspectiveVerticalFOV(float fov) { m_PerspectiveFOV = fov; RecalculateProjection(); }
		float GetPerspectiveNearClip()const { return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateProjection(); }
		float GetPerspectiveFarClip()const { return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculateProjection(); }

        // 正交投影
        float GetOrthographicSize()const { return m_OrthographicSize; }
        void SetOrthographicSize(float size) { m_OrthographicSize = size;RecalculateProjection(); }
		float GetOrthographicNearClip()const { return m_OrthographicNear; }
		void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip;RecalculateProjection(); }
		float GetOrthographicFarClip()const { return m_OrthographicFar; }
		void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip;RecalculateProjection(); }
    
        // 投影类型
        ProjectionType GetProjectionType()const { return m_ProjectionType; }
        void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalculateProjection(); }
    private:
        // 计算投影矩阵
        void RecalculateProjection();
    private:
        // 默认正交投影
        ProjectionType m_ProjectionType = ProjectionType::Orthographic; 

        float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

        float m_AspectRatio = 0.0f;
    };


}
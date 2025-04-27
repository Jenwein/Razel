#pragma once
#include "Razel/Renderer/Camera.h"

namespace Razel
{
    class SceneCamera :public Camera
    {
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        // 设置正交投影参数
        void SetOrthographic(float size, float nearClip, float farClip);
        // 设置视口尺寸
        void SetViewportSize(uint32_t width, uint32_t height);
        // 获取/设置 正交投影尺寸
        float GetOrthographicSize()const { return m_OrthographicSize; }
        void SetOrthographicSize(float size) { m_OrthographicSize = size;RecalculateProjection(); }
    private:
        // 计算投影矩阵
        void RecalculateProjection();
    private:
        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
        float m_AspectRatio = 0.0f;
    };


}
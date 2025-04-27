#pragma once
#include "Razel/Renderer/Camera.h"

namespace Razel
{
    class SceneCamera :public Camera
    {
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        // ��������ͶӰ����
        void SetOrthographic(float size, float nearClip, float farClip);
        // �����ӿڳߴ�
        void SetViewportSize(uint32_t width, uint32_t height);
        // ��ȡ/���� ����ͶӰ�ߴ�
        float GetOrthographicSize()const { return m_OrthographicSize; }
        void SetOrthographicSize(float size) { m_OrthographicSize = size;RecalculateProjection(); }
    private:
        // ����ͶӰ����
        void RecalculateProjection();
    private:
        float m_OrthographicSize = 10.0f;
        float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
        float m_AspectRatio = 0.0f;
    };


}
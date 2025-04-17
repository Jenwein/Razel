#pragma once
#include "Razel/Renderer/Framebuffer.h"

namespace Razel
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();
		
		// 创建或重新创建帧缓冲区
		void Invalidate();

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;	// 颜色缓冲,深度缓冲
		FramebufferSpecification m_Specification;		// 帧缓冲规范
	};

}
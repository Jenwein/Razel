#pragma once
#include "Razel/Core/Base.h"

namespace Razel
{
	// 帧缓冲区规范
	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		//FramebufferFormat Format =	//格式
		uint32_t Samples = 1;

		bool SwapChainTraget = false;	// 交换链目标,指示是否离屏渲染
	};

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;				// 获取颜色附件ID
		virtual const FramebufferSpecification& GetSpecification() const = 0;	// 获取帧缓冲规范

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};


}

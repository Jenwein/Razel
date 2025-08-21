#pragma once
#include "Razel/Core/Base.h"

namespace Razel
{
	// 帧缓冲纹理格式
	enum class FramebufferTextureFormat
	{
		None = 0,
		// Color
		RGBA8,
		RED_INTEGER,

		// Depth/stencil
		DEPTH24STENCIL8,

		//Defaults
		Depth = DEPTH24STENCIL8
	};

	// 帧缓冲纹理规范
	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			:TextureFormat(format){ }

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO:filtering/wrap
	};

	// 帧缓冲附件规范
	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			:Attachments(attachments) {
		}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	// 帧缓冲区规范
	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;

		bool SwapChainTraget = false;	// 交换链目标,指示是否离屏渲染
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;				// 获取颜色附件ID
		virtual const FramebufferSpecification& GetSpecification() const = 0;	// 获取帧缓冲规范

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};


}

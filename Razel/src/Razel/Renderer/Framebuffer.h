#pragma once
#include "Razel/Core/Base.h"

namespace Razel
{
	// ֡�������淶
	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		//FramebufferFormat Format =	//��ʽ
		uint32_t Samples = 1;

		bool SwapChainTraget = false;	// ������Ŀ��,ָʾ�Ƿ�������Ⱦ
	};

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;				// ��ȡ��ɫ����ID
		virtual const FramebufferSpecification& GetSpecification() const = 0;	// ��ȡ֡����淶

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};


}

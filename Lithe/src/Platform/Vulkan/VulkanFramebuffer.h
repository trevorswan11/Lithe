#pragma once

#include "Lithe/Renderer/Framebuffer.h"

namespace Lithe {

	class VulkanFramebuffer : public Framebuffer
	{
	public:
		VulkanFramebuffer(const FramebufferSpec& spec);
		virtual ~VulkanFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Invalidate() override;
		virtual void Resize(uint32_t width, uint32_t height, bool invalidate) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { LI_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }

		virtual const FramebufferSpec& GetSpec() const override { return m_Spec; }
	private:
		uint32_t m_RendererID = 0;
		FramebufferSpec m_Spec;

		std::vector<FramebufferTextureSpec> m_ColorAttachmentSpecs;
		FramebufferTextureSpec m_DepthAttachmentSpec;
		
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};

}


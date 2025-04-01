#pragma once

#include "Lithe/Core/Base.h"

namespace Lithe {

	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpec
	{
		FramebufferTextureSpec() = default;
		FramebufferTextureSpec(FramebufferTextureFormat format)
			: TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpec
	{
		FramebufferAttachmentSpec() = default;
		FramebufferAttachmentSpec(const std::initializer_list<FramebufferTextureSpec>& attachments)
			: Attachment(attachments) {}

		std::vector<FramebufferTextureSpec> Attachment;
	};

	struct FramebufferSpec
	{
		uint32_t Width, Height;
		FramebufferAttachmentSpec Attachments;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Invalidate() = 0;
		virtual void Resize(uint32_t width, uint32_t height, bool invalidate = true) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual const FramebufferSpec& GetSpec() const = 0;
		
		static Ref<Framebuffer> Create(const FramebufferSpec& spec);
	};

}



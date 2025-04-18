#include "lipch.h"
#include "DirectXFramebuffer.h"

namespace Lithe {

	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils {

		static int TextureTarget(bool multisampled)
		{
			LI_CORE_ASSERT(false);
		}

		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			LI_CORE_ASSERT(false);
		}

		static void BindTexture(bool multisampled, uint32_t id)
		{
			LI_CORE_ASSERT(false);
		}

		static void AttachColorTexture(uint32_t id, int samples, int internalFormat, int format, uint32_t width, uint32_t height, int index)
		{
			LI_CORE_ASSERT(false);
		}

		static void AttachDepthTexture(uint32_t id, int samples, int format, int attachmentType, uint32_t width, uint32_t height)
		{
			LI_CORE_ASSERT(false);
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			LI_CORE_ASSERT(false);
		}

		static int LitheFBTextureFormatToGL(FramebufferTextureFormat format)
		{
			LI_CORE_ASSERT(false);
		}

	}

	DirectXFramebuffer::DirectXFramebuffer(const FramebufferSpec& spec)
		: m_Spec(spec)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	DirectXFramebuffer::~DirectXFramebuffer()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXFramebuffer::Bind()
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXFramebuffer::Unbind()
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXFramebuffer::Invalidate()
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXFramebuffer::Resize(uint32_t width, uint32_t height, bool invalidate)
	{
		LI_CORE_ASSERT(false);
	}

	int DirectXFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		LI_CORE_ASSERT(false);
		return 0;
	}

	void DirectXFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		LI_CORE_ASSERT(false);
	}

}

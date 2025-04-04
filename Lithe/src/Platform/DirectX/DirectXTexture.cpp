#include "lipch.h"
#include "DirectXTexture.h"

#include <stb_image.h>

namespace Lithe {
	DirectXTexture2D::DirectXTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	DirectXTexture2D::DirectXTexture2D(const std::string& path)
		: m_Path(path)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	DirectXTexture2D::~DirectXTexture2D()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXTexture2D::SetData(void* data, uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXTexture2D::Bind(uint32_t slot) const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

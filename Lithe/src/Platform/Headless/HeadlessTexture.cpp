#include "lipch.h"
#include "HeadlessTexture.h"

#include <stb_image.h>

namespace Lithe {
	HeadlessTexture2D::HeadlessTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	HeadlessTexture2D::HeadlessTexture2D(const std::string& path)
		: m_Path(path)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	HeadlessTexture2D::~HeadlessTexture2D()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessTexture2D::SetData(void* data, uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessTexture2D::Bind(uint32_t slot) const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

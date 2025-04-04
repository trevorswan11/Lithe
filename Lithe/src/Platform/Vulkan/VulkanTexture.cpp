#include "lipch.h"
#include "VulkanTexture.h"

#include <stb_image.h>

namespace Lithe {
	VulkanTexture2D::VulkanTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	VulkanTexture2D::VulkanTexture2D(const std::string& path)
		: m_Path(path)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	VulkanTexture2D::~VulkanTexture2D()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanTexture2D::SetData(void* data, uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanTexture2D::Bind(uint32_t slot) const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

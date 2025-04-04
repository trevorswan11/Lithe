#include "lipch.h"
#include "VulkanBuffer.h"

namespace Lithe {

	// --------------------------- VERTEX BUFFER ---------------------------

	VulkanVertexBuffer::VulkanVertexBuffer(uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);

	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanVertexBuffer::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanVertexBuffer::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanVertexBuffer::SetData(const void* data, uint32_t size)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	// --------------------------- INDEX BUFFER ---------------------------

	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanIndexBuffer::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanIndexBuffer::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

#include "lipch.h"
#include "VulkanBuffer.h"

#include <glad/glad.h>

namespace Lithe {

	// --------------------------- VERTEX BUFFER ---------------------------

	VulkanVertexBuffer::VulkanVertexBuffer(uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		LI_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void VulkanVertexBuffer::Bind() const
	{
		LI_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VulkanVertexBuffer::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VulkanVertexBuffer::SetData(const void* data, uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	// --------------------------- INDEX BUFFER ---------------------------

	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		LI_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
		LI_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void VulkanIndexBuffer::Bind() const
	{
		LI_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void VulkanIndexBuffer::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

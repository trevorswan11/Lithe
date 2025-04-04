#include "lipch.h"
#include "HeadlessBuffer.h"

namespace Lithe {

	// --------------------------- VERTEX BUFFER ---------------------------

	HeadlessVertexBuffer::HeadlessVertexBuffer(uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	HeadlessVertexBuffer::HeadlessVertexBuffer(float* vertices, uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);

	}

	HeadlessVertexBuffer::~HeadlessVertexBuffer()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessVertexBuffer::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessVertexBuffer::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessVertexBuffer::SetData(const void* data, uint32_t size)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	// --------------------------- INDEX BUFFER ---------------------------

	HeadlessIndexBuffer::HeadlessIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	HeadlessIndexBuffer::~HeadlessIndexBuffer()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessIndexBuffer::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessIndexBuffer::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

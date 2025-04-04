#include "lipch.h"
#include "DirectXBuffer.h"

namespace Lithe {

	// --------------------------- VERTEX BUFFER ---------------------------

	DirectXVertexBuffer::DirectXVertexBuffer(uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	DirectXVertexBuffer::DirectXVertexBuffer(float* vertices, uint32_t size)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);

	}

	DirectXVertexBuffer::~DirectXVertexBuffer()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXVertexBuffer::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXVertexBuffer::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXVertexBuffer::SetData(const void* data, uint32_t size)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	// --------------------------- INDEX BUFFER ---------------------------

	DirectXIndexBuffer::DirectXIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	DirectXIndexBuffer::~DirectXIndexBuffer()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXIndexBuffer::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXIndexBuffer::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

#include "lipch.h"
#include "HeadlessVertexArray.h"

#include <glad/glad.h>

namespace Lithe {

	static int ShaderDataTypeToHeadlessBaseType(ShaderDataType type)
	{
		LI_CORE_ASSERT(false);
	}

	HeadlessVertexArray::HeadlessVertexArray()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	HeadlessVertexArray::~HeadlessVertexArray()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessVertexArray::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessVertexArray::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

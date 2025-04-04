#include "lipch.h"
#include "DirectXRendererAPI.h"

namespace Lithe {

	void DirectXMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXRendererAPI::Init()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXRendererAPI::SetClearColor(const glm::vec4& color)
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXRendererAPI::Clear()
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		LI_CORE_ASSERT(false);
	}

	void DirectXRendererAPI::SetLineWidth(float width)
	{
		LI_CORE_ASSERT(false);
	}

}

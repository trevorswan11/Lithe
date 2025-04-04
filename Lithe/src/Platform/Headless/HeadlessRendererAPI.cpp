#include "lipch.h"
#include "HeadlessRendererAPI.h"

namespace Lithe {

	void HeadlessMessageCallback(
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

	void HeadlessRendererAPI::Init()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		LI_CORE_ASSERT(false);
	}

	void HeadlessRendererAPI::SetClearColor(const glm::vec4& color)
	{
		LI_CORE_ASSERT(false);
	}

	void HeadlessRendererAPI::Clear()
	{
		LI_CORE_ASSERT(false);
	}

	void HeadlessRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		LI_CORE_ASSERT(false);
	}

	void HeadlessRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		LI_CORE_ASSERT(false);
	}

	void HeadlessRendererAPI::SetLineWidth(float width)
	{
		LI_CORE_ASSERT(false);
	}

}

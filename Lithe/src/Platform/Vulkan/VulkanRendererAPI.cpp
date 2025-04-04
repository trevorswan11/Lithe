#include "lipch.h"
#include "VulkanRendererAPI.h"

namespace Lithe {

	void VulkanMessageCallback(
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

	void VulkanRendererAPI::Init()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		LI_CORE_ASSERT(false);
	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
		LI_CORE_ASSERT(false);
	}

	void VulkanRendererAPI::Clear()
	{
		LI_CORE_ASSERT(false);
	}

	void VulkanRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		LI_CORE_ASSERT(false);
	}

	void VulkanRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		LI_CORE_ASSERT(false);
	}

	void VulkanRendererAPI::SetLineWidth(float width)
	{
		LI_CORE_ASSERT(false);
	}

}

#include "lipch.h"
#include "VulkanRendererAPI.h"

#include <glad/glad.h>

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
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         LI_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       LI_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          LI_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: LI_CORE_TRACE(message); return;
		}

		LI_CORE_ASSERT(false, "Unknown severity level!");
	}

	void VulkanRendererAPI::Init()
	{
		LI_PROFILE_FUNCTION();

		#ifdef LI_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(VulkanMessageCallback, nullptr);

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void VulkanRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void VulkanRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void VulkanRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void VulkanRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void VulkanRendererAPI::SetLineWidth(float width)
	{
		glLineWidth(std::min(width, 1.0f)); // in future versions, width > 1.0f is deprecated
	}

}

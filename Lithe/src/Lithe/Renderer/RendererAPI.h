#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Lithe {

	class LITHE_API RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			DirectX = 2,
			Vulcan = 3
		};
	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static inline API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}
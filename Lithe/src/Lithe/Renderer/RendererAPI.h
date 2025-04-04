#pragma once

#include "Lithe/Core/Base.h"

#include "Lithe/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Lithe {

	class RendererAPI
	{
	public:
		enum class API
		{
			Headless = 0,
			OpenGL = 1,
			DirectX = 2,
			Vulkan = 3
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

		virtual void SetLineWidth(float width) = 0;

		static inline API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static void SetRendererAPI(int api, bool forceOpenGL = true)
		{
			if (forceOpenGL)
			{
				s_API = API::OpenGL;
			}
			else
			{
				switch (api)
				{
					case 0:
					case 1:
					case 2:
					case 3:
						s_API = (API)api;
						break;
					default:
						LI_CORE_ASSERT(false, "Failed to set Renderer API");
				}
			}
			LI_CORE_WARN("Renderer API set to {0}.", IntToRendererAPIString(forceOpenGL ? 1 : api));
		}

		static std::string IntToRendererAPIString(int api)
		{
			switch (api)
			{
				case 0:
					return "Headless";
				case 1:
					return "OpenGL";
				case 2:
					return "DirectX";
				case 3:
					return "Vulkan";
				default:
					return std::string();
			}
		}
	private:
		static API s_API;

		friend class Application;
	};

}

#pragma once

#include "Lithe/Core.h"

namespace Lithe {

	enum class LITHE_API RendererAPI
	{
		None = 0,
		OpenGL = 1,
		DirectX = 2,
		Vulcan = 3
	};

	class LITHE_API Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
		inline static RendererAPI SetAPI(RendererAPI API) { s_RendererAPI = API; }
	private:
		static RendererAPI s_RendererAPI;
	};
}
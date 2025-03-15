#include "lipch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lithe {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}

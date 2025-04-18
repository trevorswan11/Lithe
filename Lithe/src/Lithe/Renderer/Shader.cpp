#include "lipch.h"
#include "Shader.h"

#include "Lithe/Renderer/Renderer.h"

#include "Platform/Headless/HeadlessShader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/Vulkan/VulkanShader.h"
#include "Platform/DirectX/DirectXShader.h"

namespace Lithe {
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessShader>(filepath);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLShader>(filepath);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanShader>(filepath);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXShader>(filepath);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::Headless:	return CreateRef<HeadlessShader>(name, vertexSrc, fragmentSrc);
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
			case RendererAPI::API::Vulkan:		return CreateRef<VulkanShader>(name, vertexSrc, fragmentSrc);
			case RendererAPI::API::DirectX:		return CreateRef<DirectXShader>(name, vertexSrc, fragmentSrc);
		}

		LI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		LI_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		LI_CORE_ASSERT(Exists(name), "Shader does not exist!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}

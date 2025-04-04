#include "lipch.h"
#include "DirectXShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#pragma warning(push, 0)
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#pragma warning(pop)

#include "Lithe/Core/Timer.h"

namespace Lithe {

	namespace Utils {

		static int ShaderTypeFromString(const std::string& type)
		{
			LI_CORE_ASSERT(false);
			return 0;
		}

		static shaderc_shader_kind GLShaderStageToShaderC(int stage)
		{
			LI_CORE_ASSERT(false);
			return (shaderc_shader_kind)0;
		}

		static const char* GLShaderStageToString(int stage)
		{
			LI_CORE_ASSERT(false);
			return nullptr;
		}

		static const char* GetCacheDirectory() // TODO: make sure the assets directory is valid
		{
			return "assets/cache/shader/vulkan";
		}

		static const char* GetHashDirectory() // TODO: use for shader serialization
		{
			return "assets/cache/shader/vulkan/hash";
		}

		static void CreateCacheDirectoryIfNeeded()
		{
			std::string cacheDirectory = GetCacheDirectory();
			if (!std::filesystem::exists(cacheDirectory))
				std::filesystem::create_directories(cacheDirectory);
		}

		static void CreateHashDirectoryIfNeeded()
		{
			std::string cacheDirectory = GetHashDirectory();
			if (!std::filesystem::exists(cacheDirectory))
				std::filesystem::create_directories(cacheDirectory);
		}

		static const char* DirectXShaderStageCachedDirectXFileExtension(uint32_t stage)
		{
			LI_CORE_ASSERT(false);
			return "";
		}

	}


	DirectXShader::DirectXShader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	DirectXShader::DirectXShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	DirectXShader::~DirectXShader()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	std::string DirectXShader::ReadFile(const std::string& filepath)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
		return std::string();
	}

	std::unordered_map<int, std::string> DirectXShader::PreProcess(const std::string& source)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
		return {};
	}

	void DirectXShader::CompileOrGetDirectXBinaries(const std::unordered_map<int, std::string>& shaderSources)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXShader::CompileOrGetDirectXBinaries()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXShader::CreateProgram()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXShader::Reflect(int stage, const std::vector<uint32_t>& shaderData)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXShader::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXShader::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXShader::SetInt(const std::string& name, int value)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void DirectXShader::SetFloat(const std::string& name, float value)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void DirectXShader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void DirectXShader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void DirectXShader::SetMat4(const std::string& name, const glm::mat4& values)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

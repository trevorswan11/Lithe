#include "lipch.h"
#include "VulkanShader.h"

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#pragma warning(push, 0)
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>
#pragma warning(pop)

#include "Lithe/Core/Timer.h"

namespace Lithe {

	namespace Utils {

		static const char* GetCacheDirectory()
		{
			LI_CORE_ASSERT(std::filesystem::exists("assets"));
			return "assets/cache/shader/vulkan";
		}

		static const char* GetHashDirectory()
		{
			LI_CORE_ASSERT(std::filesystem::exists("assets"));
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

	}


	VulkanShader::VulkanShader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	VulkanShader::VulkanShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	VulkanShader::~VulkanShader()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	std::string VulkanShader::ReadFile(const std::string& filepath)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
		return std::string();
	}

	std::unordered_map<int, std::string> VulkanShader::PreProcess(const std::string& source)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
		return {};
	}

	void VulkanShader::CompileOrGetVulkanBinaries(const std::unordered_map<int, std::string>& shaderSources)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanShader::CompileOrGetVulkanBinaries()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanShader::CreateProgram()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanShader::Reflect(int stage, const std::vector<uint32_t>& shaderData)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanShader::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanShader::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanShader::SetInt(const std::string& name, int value)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void VulkanShader::SetFloat(const std::string& name, float value)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void VulkanShader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void VulkanShader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void VulkanShader::SetMat4(const std::string& name, const glm::mat4& values)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

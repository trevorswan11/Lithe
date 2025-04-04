#include "lipch.h"
#include "DirectXShader.h"

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include "Lithe/Core/Timer.h"

namespace Lithe {

	namespace Utils {

		static const char* GetCacheDirectory()
		{
			LI_CORE_ASSERT(std::filesystem::exists("assets"));
			return "assets/cache/shader/directx";
		}

		static const char* GetHashDirectory()
		{
			LI_CORE_ASSERT(std::filesystem::exists("assets"));
			return "assets/cache/shader/directx/hash";
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

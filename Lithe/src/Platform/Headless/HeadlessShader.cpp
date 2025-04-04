#include "lipch.h"
#include "HeadlessShader.h"

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include "Lithe/Core/Timer.h"

namespace Lithe {

	namespace Utils {

		static const char* GetCacheDirectory()
		{
			LI_CORE_ASSERT(std::filesystem::exists("assets"));
			return "assets/cache/shader/headless";
		}

		static const char* GetHashDirectory()
		{
			LI_CORE_ASSERT(std::filesystem::exists("assets"));
			return "assets/cache/shader/headless/hash";
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


	HeadlessShader::HeadlessShader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	HeadlessShader::HeadlessShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	HeadlessShader::~HeadlessShader()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	std::string HeadlessShader::ReadFile(const std::string& filepath)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
		return std::string();
	}

	std::unordered_map<int, std::string> HeadlessShader::PreProcess(const std::string& source)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
		return {};
	}

	void HeadlessShader::CompileOrGetHeadlessBinaries(const std::unordered_map<int, std::string>& shaderSources)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::CompileOrGetHeadlessBinaries()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::CreateProgram()
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::Reflect(int stage, const std::vector<uint32_t>& shaderData)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::Bind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::SetInt(const std::string& name, int value)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::SetFloat(const std::string& name, float value)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		LI_PROFILE_FUNCTION();
	
		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

	void HeadlessShader::SetMat4(const std::string& name, const glm::mat4& values)
	{
		LI_PROFILE_FUNCTION();

		LI_CORE_ASSERT(false);
	}

}

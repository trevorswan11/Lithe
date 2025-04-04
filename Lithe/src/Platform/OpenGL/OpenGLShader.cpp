#include "lipch.h"
#include "OpenGLShader.h"

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

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")	return GL_VERTEX_SHADER;
			if (type == "fragment")	return GL_FRAGMENT_SHADER;
			if (type == "pixel")	return GL_FRAGMENT_SHADER;

			LI_CORE_ASSERT(false);
			return 0;
		}

		static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
		{
			switch (stage)
			{
				case GL_VERTEX_SHADER:		return shaderc_glsl_vertex_shader;
				case GL_FRAGMENT_SHADER:	return shaderc_glsl_fragment_shader;
			}
			LI_CORE_ASSERT(false);
			return (shaderc_shader_kind)0;
		}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
				case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
				case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
			}
			LI_CORE_ASSERT(false);
			return nullptr;
		}

		static const char* GetCacheDirectory() // TODO: make sure the assets directory is valid
		{
			return "assets/cache/shader/opengl";
		}

		static const char* GetHashDirectory() // TODO: use for shader serialization
		{
			return "assets/cache/shader/opengl/hash";
		}

		static size_t HashShaderString(const std::string& source)
		{
			return std::hash<std::string>{}(source);
		}

		static void CreateCacheDirectoryIfNeeded()
		{
			std::string cacheDirectory = GetCacheDirectory();
			if (!std::filesystem::exists(cacheDirectory))
				std::filesystem::create_directories(cacheDirectory);
		}

		static void CreateHashDirectoryIfNeeded()
		{
			std::string hashDirectory = GetHashDirectory();
			if (!std::filesystem::exists(hashDirectory))
				std::filesystem::create_directories(hashDirectory);
		}

		static const char* GLShaderStageCachedOpenGLFileExtension(uint32_t stage)
		{
			switch (stage)
			{
				case GL_VERTEX_SHADER:    return ".cached_opengl.vert";
				case GL_FRAGMENT_SHADER:  return ".cached_opengl.frag";
			}
			LI_CORE_ASSERT(false);
			return "";
		}

		static const char* GLShaderStageCachedVulkanFileExtension(uint32_t stage)
		{
			switch (stage)
			{
				case GL_VERTEX_SHADER:    return ".cached_vulkan.vert";
				case GL_FRAGMENT_SHADER:  return ".cached_vulkan.frag";
			}
			LI_CORE_ASSERT(false);
			return "";
		}

		static std::filesystem::path GetOpenGLHashFilePath(const std::filesystem::path& basePath, GLenum stage)
		{
			return std::filesystem::path(Utils::GetHashDirectory()) / (basePath.filename().string() + Utils::GLShaderStageCachedOpenGLFileExtension(stage) + ".hash");
		}

		static std::filesystem::path GetVulkanHashFilePath(const std::filesystem::path& basePath, GLenum stage)
		{
			return std::filesystem::path(Utils::GetHashDirectory()) / (basePath.filename().string() + Utils::GLShaderStageCachedVulkanFileExtension(stage) + ".hash");
		}
	}


	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		LI_PROFILE_FUNCTION();

		Utils::CreateCacheDirectoryIfNeeded();
		Utils::CreateHashDirectoryIfNeeded();

		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		
		{
			Timer timer;
			CompileOrGetVulkanBinaries(shaderSources);
			CompileOrGetOpenGLBinaries();
			CreateProgram();
			LI_CORE_WARN("Shader creation took {0} ms", timer.ElapsedMillis());
		}

		// Extract name from filepath
		// EXAMPLE: assets/shaders/Texture.glsl
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		LI_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::pair<std::string, bool>> sources;
		sources[GL_VERTEX_SHADER].first = vertexSrc;
		sources[GL_FRAGMENT_SHADER].first = fragmentSrc;
		
		CompileOrGetVulkanBinaries(sources);
		CompileOrGetOpenGLBinaries();
		CreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		LI_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath) // TODO: Add to FileUtils header
	{
		LI_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
		}
		else
		{
			LI_CORE_ERROR("Could not open file `{0}`", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::pair<std::string, bool>> OpenGLShader::PreProcess(const std::string& source)
	{
		LI_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::pair<std::string, bool>> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			LI_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			LI_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			LI_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);
			shaderSources[Utils::ShaderTypeFromString(type)] = { (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos), true };
		}

		return shaderSources;
	}

	// TODO: Shader serialization with hashing
	void OpenGLShader::CompileOrGetVulkanBinaries(std::unordered_map<GLenum, std::pair<std::string, bool>>& shaderSources)
	{
		LI_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2); // Compatible with vulkan 1.2.
		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDirectory = Utils::GetCacheDirectory();

		auto& shaderData = m_VulkanSPIRV;
		shaderData.clear();
		for (auto&& [stage, source] : shaderSources)
		{
			std::filesystem::path shaderFilePath = m_FilePath;
			std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + Utils::GLShaderStageCachedVulkanFileExtension(stage));
			
			// Check hash for serialization
			size_t sourceHash = Utils::HashShaderString(source.first);
			auto hashPath = Utils::GetVulkanHashFilePath(shaderFilePath, stage);
			shaderData[stage].second = true;
			if (std::filesystem::exists(hashPath))
			{
				std::ifstream hashIn(hashPath);
				size_t cachedHash;
				hashIn >> cachedHash;
				if (cachedHash == sourceHash && std::filesystem::exists(cachedPath))
				{
					// Hashes match and cache exists, so we can load from disk
					std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
					if (in.is_open())
					{
						in.seekg(0, std::ios::end);
						auto size = in.tellg();
						in.seekg(0, std::ios::beg);
						auto& data = shaderData[stage].first;
						data.resize(size / sizeof(uint32_t));
						in.read((char*)data.data(), size);
					}
					LI_CORE_INFO("{0}: Compilation skipped as no changes were detected.", shaderFilePath.filename().string() + " - " + Utils::GLShaderStageToString(stage));
					source.second = false;
					shaderData[stage].second = false;
				}
			}
			
			if (source.second)
			{
				// Compile the shader as usual
				LI_CORE_WARN("Compiling Shader: {0}", shaderFilePath.filename().string() + " - " + Utils::GLShaderStageToString(stage));
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source.first, Utils::GLShaderStageToShaderC(stage), m_FilePath.c_str(), options);
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					LI_CORE_ERROR(module.GetErrorMessage());
					LI_CORE_ASSERT(false);
				}

				shaderData[stage].first = std::vector<uint32_t>(module.cbegin(), module.cend());

				{
					LI_PROFILE_SCOPE("Write Shader Binary");

					std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
					if (out.is_open())
					{
						auto& data = shaderData[stage].first;
						out.write((char*)data.data(), data.size() * sizeof(uint32_t));
						out.flush();
						out.close();
					}
				}

				{
					LI_PROFILE_SCOPE("Write Shader Hash");

					std::ofstream out(hashPath, std::ios::out);
					if (out.is_open())
					{
						out << sourceHash;
						out.flush();
						out.close();
					}
				}
			}

			for (auto&& [stage, data] : shaderData)
				Reflect(stage, data.first);
		}
	}

	void OpenGLShader::CompileOrGetOpenGLBinaries()
	{
		LI_PROFILE_FUNCTION();

		auto& shaderData = m_OpenGLSPIRV;

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDirectory = Utils::GetCacheDirectory();

		shaderData.clear();
		m_OpenGLSourceCode.clear();
		for (auto&& [stage, spirv] : m_VulkanSPIRV)
		{
			std::filesystem::path shaderFilePath = m_FilePath;
			std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + Utils::GLShaderStageCachedOpenGLFileExtension(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (!spirv.second && in.is_open())
			{
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage].first;
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else
			{
				spirv_cross::CompilerGLSL glslCompiler(spirv.first);
				m_OpenGLSourceCode[stage].first = glslCompiler.compile();
				auto& source = m_OpenGLSourceCode[stage].first;

				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), m_FilePath.c_str());
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					LI_CORE_ERROR(module.GetErrorMessage());
					LI_CORE_ASSERT(false);
				}

				shaderData[stage].first = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = shaderData[stage].first;
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}
	}

	void OpenGLShader::CreateProgram()
	{
		LI_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : m_OpenGLSPIRV)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.first.data(), (GLsizei)(spirv.first.size() * sizeof(uint32_t)));
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
		}

		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			LI_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_FilePath, infoLog.data());

			glDeleteProgram(program);

			for (auto id : shaderIDs)
				glDeleteShader(id);
		}

		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_RendererID = program;
	}

	void OpenGLShader::Reflect(GLenum stage, const std::vector<uint32_t>& shaderData)
	{
		LI_PROFILE_FUNCTION();

		spirv_cross::Compiler compiler(shaderData);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		LI_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", Utils::GLShaderStageToString(stage), m_FilePath);
		LI_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
		LI_CORE_TRACE("    {0} resources", resources.sampled_images.size());

		LI_CORE_TRACE("Uniform buffers:");
		for (const auto& resource : resources.uniform_buffers)
		{
			const auto& bufferType = compiler.get_type(resource.base_type_id);
			uint32_t bufferSize = static_cast<uint32_t>(compiler.get_declared_struct_size(bufferType));
			uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			int memberCount = static_cast<int>(bufferType.member_types.size());

			LI_CORE_TRACE("  {0}", resource.name);
			LI_CORE_TRACE("    Size = {0}", bufferSize);
			LI_CORE_TRACE("    Binding = {0}", binding);
			LI_CORE_TRACE("    Members = {0}", memberCount);
		}
	}

	void OpenGLShader::Bind() const
	{
		LI_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		LI_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		LI_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		LI_PROFILE_FUNCTION();

		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		LI_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		LI_PROFILE_FUNCTION();

		UploadUniformFloat3(name, values);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		LI_PROFILE_FUNCTION();

		UploadUniformFloat4(name, values);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& values)
	{
		LI_PROFILE_FUNCTION();

		UploadUniformMat4(name, values);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, static_cast<GLint>(value));
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::vec2& values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2i(location, static_cast<GLint>(values.x), static_cast<GLint>(values.y));
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::vec3& values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3i(location,
			static_cast<GLint>(values.x),
			static_cast<GLint>(values.y),
			static_cast<GLint>(values.z)
		);
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::vec4& values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4i(location,
			static_cast<GLint>(values.x),
			static_cast<GLint>(values.y),
			static_cast<GLint>(values.z),
			static_cast<GLint>(values.w)
		);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}

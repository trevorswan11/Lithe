#pragma once

#include "Lithe/Renderer/Shader.h"

#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;
constexpr auto MAX_ALLOWED_SHADERS = 2;

namespace Lithe {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& values) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& values) override;

		virtual const std::string& GetName() const override { return m_Name; };

		void UploadUniformInt(const std::string& name, int value) const;
		void UploadUniformInt2(const std::string& name, const glm::vec2& values) const;
		void UploadUniformInt3(const std::string& name, const glm::vec3& values) const;
		void UploadUniformInt4(const std::string& name, const glm::vec4& values) const;

		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count) const;

		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values) const;
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values) const;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values) const;

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
	private:
		// These private functions are incredibly complex compared to the rest of the project.
		// Functions were mostly written by The Cherno, as I do not understand the Vulkan API
		// as much as I understood OpenGL. Vulkan is the way though.

		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::pair<std::string, bool>> PreProcess(const std::string& source);

		void CompileOrGetVulkanBinaries(std::unordered_map<GLenum, std::pair<std::string, bool>>& shaderSources);
		void CompileOrGetOpenGLBinaries();
		void CreateProgram();
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
	private:
		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<GLenum, std::pair<std::vector<uint32_t>, bool>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::pair<std::vector<uint32_t>, bool>> m_OpenGLSPIRV;

		std::unordered_map<GLenum, std::pair<std::string, bool>> m_OpenGLSourceCode;
	};

}


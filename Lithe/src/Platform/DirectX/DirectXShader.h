#pragma once

#include "Lithe/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Lithe {

	class DirectXShader : public Shader
	{
	public:
		DirectXShader(const std::string& filepath);
		DirectXShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~DirectXShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& values) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& values) override;

		virtual const std::string& GetName() const override { return m_Name; };
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<int, std::string> PreProcess(const std::string& source);
		
		void CompileOrGetDirectXBinaries(const std::unordered_map<int, std::string>& shaderSources);
		void CompileOrGetDirectXBinaries();
		void CreateProgram();
		void Reflect(int stage, const std::vector<uint32_t>& shaderData);
	private:
		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<int, std::vector<uint32_t>> m_DirectXSPIRV;

		std::unordered_map<int, std::string> m_DirectXSourceCode;
	};

}


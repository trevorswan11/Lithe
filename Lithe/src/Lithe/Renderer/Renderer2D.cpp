#include "lipch.h"
#include "Renderer2D.h"

#include "Lithe/Renderer/VertexArray.h"
#include "Lithe/Renderer/Shader.h"
#include "Lithe/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Lithe {

	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData();
		s_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f ,0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f 
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	// ---- Base Quad Drawing ----

	// Draws a quad with a given color and optional scale factor for the texture at the base (0) z-level
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float textureScale)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, textureScale);
	}

	// Draws a quad with a given texture and optional scale factor for the texture at the base (0) z-level
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float textureScale)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, textureScale);
	}

	// Draws a quad with a given colored texture and optional scale factor for the texture at the base (0) z-level
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& color, float textureScale)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, color, textureScale);
	}

	// Draws a quad with a given color and optional scale factor for the texture at the given z-level
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float textureScale)
	{
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TextureScale", textureScale);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	// Draws a quad with a given texture and optional scale factor for the texture at the given z-level
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float textureScale)
	{
		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		s_Data->TextureShader->SetFloat("u_TextureScale", textureScale);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	// Draws a quad with a given colored texture and optional scale factor for the texture at the given z-level
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& color, float textureScale)
	{
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TextureScale", textureScale);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	// ---- Rotated Quad Drawing ----

	// Draws a rotated quad with a given color and optional scale factor for the texture at the base (0) z-level
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color, float textureScale)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, color, textureScale);
	}

	// Draws a rotated quad with a given texture and optional scale factor for the texture at the base (0) z-level
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, float textureScale)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture, textureScale);
	}

	// Draws a rotated quad with a given colored texture and optional scale factor for the texture at the base (0) z-level
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& color, float textureScale)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture, color, textureScale);
	}

	// Draws a rotated quad with a given color and optional scale factor for the texture at the given z-level
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color, float textureScale)
	{
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TextureScale", textureScale);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) 
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	// Draws a rotated quad with a given texture and optional scale factor for the texture at the given z-level
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, float textureScale)
	{
		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		s_Data->TextureShader->SetFloat("u_TextureScale", textureScale);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	// Draws a rotated quad with a given colored texture and optional scale factor for the texture at the given z-level
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& color, float textureScale)
	{
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TextureScale", textureScale);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}
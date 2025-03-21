#pragma once

#include "Lithe/Core/Base.h"

#include "Lithe/Renderer/OrthographicCamera.h"

#include "Lithe/Renderer/Texture.h"

namespace Lithe {

	struct QuadProperties
	{
	public:
		QuadProperties(bool useRadians = false)
			: m_UseRadians(useRadians) {}
	public:
		inline void SetPosition(const glm::vec2& position) { m_Position = glm::vec3(position, 0.0f); }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; }
		inline void SetSize(const glm::vec2& size) { m_Size = size; }
		inline void SetTexture(const Ref<Texture2D>& texture) { m_Texture = texture; }
		inline void SetColor(const glm::vec4& color) { m_Color = color; }
		inline void SetTextureScale(float textureScale) { m_TextureScale = textureScale; }
		inline void SetRoation(float rotation) { m_RotationDegrees = m_UseRadians ? glm::degrees(rotation) : rotation; }
	public:
		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec2 GetSize() const { return m_Size; }
		const Ref<Texture2D>& GetTexture() const { return m_Texture; }
		glm::vec4 GetColor() const { return m_Color; }
		float GetTextureScale() const { return m_TextureScale; }
		float GetRotationDegrees() const { return m_RotationDegrees; }
	private:
		glm::vec3		m_Position;
		glm::vec2		m_Size;
		Ref<Texture2D>	m_Texture;
		glm::vec4		m_Color;
		float			m_TextureScale = 1.0f;
		float			m_RotationDegrees = 0.0f;
	private:
		bool			m_UseRadians;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();
	private:
		static void FlushAndReset();
	public:
		// ---- Base Quad Drawing ----

		// === OVERLOADS ===

		inline static void DrawQuad(const QuadProperties& properties)
		{
			DrawQuad(
				properties.GetPosition(),
				properties.GetSize(),
				properties.GetTexture(),
				properties.GetColor(),
				properties.GetTextureScale()
			);
		}

		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{
			DrawQuad({ position.x, position.y, 0.0f }, size, color);
		}

		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawQuad({ position.x, position.y, 0.0f }, size, texture, textureScale);
		}
		
		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f)
		{
			DrawQuad({ position.x, position.y, 0.0f }, size, texture, color, textureScale);
		}
		
		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		{
			auto whiteTexture = Texture2D::Create(1, 1);
			uint32_t whiteTextureData = 0xffffffff;
			whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

			DrawQuad(position, size, whiteTexture, color, 1.0f);
		}
		
		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawQuad(position, size, texture, glm::vec4(1.0f), textureScale);
		}
		
		// === IMPL ===

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);

		// ---- Rotated Quad Drawing ----

		// === OVERLOADS ===

		static void Renderer2D::DrawRotatedQuad(const QuadProperties& properties)
		{
			DrawRotatedQuad(
				properties.GetPosition(),
				properties.GetRotationDegrees(),
				properties.GetSize(),
				properties.GetTexture(),
				properties.GetColor(),
				properties.GetTextureScale()
			);
		}

		inline static void DrawRotatedQuad(const glm::vec2& position, float degrees, const glm::vec2& size, const glm::vec4& color)
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, degrees, size, color);
		}

		inline static void DrawRotatedQuad(const glm::vec2& position, float degrees, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, degrees, size, texture, textureScale);
		}
		
		inline static void DrawRotatedQuad(const glm::vec2& position, float degrees, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f)
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, degrees, size, texture, color, textureScale);
		}
		
		inline static void DrawRotatedQuad(const glm::vec3& position, float degrees, const glm::vec2& size, const glm::vec4& color)
		{
			auto whiteTexture = Texture2D::Create(1, 1);
			uint32_t whiteTextureData = 0xffffffff;
			whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

			DrawRotatedQuad(position, degrees, size, whiteTexture, color, 1.0f);
		}
		
		inline static void DrawRotatedQuad(const glm::vec3& position, float degrees, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawRotatedQuad(position, degrees, size, texture, glm::vec4(1.0f), textureScale);
		}
		
		// === IMPL ===

		static void DrawRotatedQuad(const glm::vec3& position, float degrees, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);

		// --- Stats ---

		struct Stats
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const { return QuadCount * 4; };
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; };
		};
		static void ResetStats();
		static Stats GetStats();
	};

}
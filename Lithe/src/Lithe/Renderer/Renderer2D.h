#pragma once

#include "Lithe/Core/Base.h"

#include "Lithe/Renderer/OrthographicCamera.h"

#include "Lithe/Renderer/Texture.h"

namespace Lithe {

	struct QuadProperties
	{
	public:
		QuadProperties(bool useRadians = false)
			: m_UseRadians(useRadians) {
		}
	public:
		inline void SetPosition(const glm::vec2& position) { m_Position = glm::vec3(position, 0.0f); }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; }
		inline void SetSize(const glm::vec2& size) { m_Size = size; }
		inline void SetTexture(const Ref<Texture2D>& texture) { m_Texture = texture; }
		inline void SetColor(const glm::vec4& color) { m_Color = color; }
		inline void SetTextureScale(float textureScale) { m_TextureScale = textureScale; }
		inline void SetRoation(float rotation) { m_Rotation = m_UseRadians ? rotation : glm::radians(rotation); }
	public:
		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec2 GetSize() const { return m_Size; }
		const Ref<Texture2D>& GetTexture() const { return m_Texture; }
		glm::vec4 GetColor() const { return m_Color; }
		float GetTextureScale() const { return m_TextureScale; }
		float GetRotation() const { return m_Rotation; }
	private:
		glm::vec3		m_Position;
		glm::vec2		m_Size;
		Ref<Texture2D>	m_Texture;
		glm::vec4		m_Color;
		float			m_TextureScale = 1.0f;
		float			m_Rotation = 0.0f;
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

		// ---- Base Quad Drawing ----
		static void DrawQuad(const QuadProperties& properties);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colorf);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);

		// ---- Rotated Quad Drawing ----
		static void DrawRotatedQuad(const QuadProperties& properties);

		static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);
	};

}
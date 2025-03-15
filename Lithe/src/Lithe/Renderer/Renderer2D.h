#pragma once

#include "Lithe/Core/Base.h"

#include "Lithe/Renderer/OrthographicCamera.h"

#include "Lithe/Renderer/Texture.h"

namespace Lithe {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// ---- Base Quad Drawing ----

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& color, float textureScale = 1.0f);

		// ---- Rotated Quad Drawing ----

		static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& color, float textureScale = 1.0f);
	};

}
#pragma once

#include "Lithe/Core/Base.h"

#include "Lithe/Renderer/Camera.h"
#include "Lithe/Renderer/OrthographicCamera.h"

#include "Lithe/Renderer/Texture.h"
#include "Lithe/Renderer/SubTexture2D.h"

namespace Lithe {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera); // TODO: remove
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void EndScene();
		static void Flush();
	private:
		static void StartBatch();
		static void NextBatch();
	public:
		// ---- Base Quad Drawing ----

		// === OVERLOADS ===

		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{
			DrawQuad({ position.x, position.y, 0.0f }, size, color);
		}

		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		{
			DrawQuad(position, size, (Ref<Texture2D>)nullptr, color);
		}

		inline static void DrawQuad(const glm::mat4& transform, const glm::vec4& color)
		{
			DrawQuad(transform, (Ref<Texture2D>)nullptr, color);
		}

		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawQuad({ position.x, position.y, 0.0f }, size, texture, textureScale);
		}

		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float textureScale = 1.0f)
		{
			DrawQuad({ position.x, position.y, 0.0f }, size, subTexture, textureScale);
		}

		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawQuad(position, size, texture, glm::vec4(1.0f), textureScale);
		}

		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float textureScale = 1.0f)
		{
			DrawQuad(position, size, subTexture, glm::vec4(1.0f), textureScale);
		}

		inline static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawQuad(transform, texture, glm::vec4(1.0f), textureScale);
		}

		inline static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, float textureScale = 1.0f)
		{
			DrawQuad(transform, subTexture, glm::vec4(1.0f), textureScale);
		}
		
		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f)
		{
			DrawQuad({ position.x, position.y, 0.0f }, size, texture, color, textureScale);
		}

		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& color, float textureScale = 1.0f)
		{
			DrawQuad({ position.x, position.y, 0.0f }, size, subTexture, color, textureScale);
		}
		
		// === IMPL ===

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& color, float textureScale = 1.0f);

		// ---- Rotated Quad Drawing ----

		// === OVERLOADS ===

		inline static void DrawRotatedQuad(const glm::vec2& position, float rotationRadians, const glm::vec2& size, const glm::vec4& color)
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, rotationRadians, size, color);
		}

		inline static void DrawRotatedQuad(const glm::vec3& position, float rotationRadians, const glm::vec2& size, const glm::vec4& color)
		{
			DrawRotatedQuad(position, rotationRadians, size, (Ref<Texture2D>)nullptr, color, 1.0f);
		}

		inline static void DrawRotatedQuad(const glm::vec2& position, float rotationRadians, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, rotationRadians, size, texture, textureScale);
		}

		inline static void DrawRotatedQuad(const glm::vec2& position, float rotationRadians, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float textureScale = 1.0f)
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, rotationRadians, size, subTexture, textureScale);
		}
		
		inline static void DrawRotatedQuad(const glm::vec3& position, float rotationRadians, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f)
		{
			DrawRotatedQuad(position, rotationRadians, size, texture, glm::vec4(1.0f), textureScale);
		}

		inline static void DrawRotatedQuad(const glm::vec3& position, float rotationRadians, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float textureScale = 1.0f)
		{
			DrawRotatedQuad(position, rotationRadians, size, subTexture, glm::vec4(1.0f), textureScale);
		}

		inline static void DrawRotatedQuad(const glm::vec2& position, float rotationRadians, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f)
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, rotationRadians, size, texture, color, textureScale);
		}

		inline static void DrawRotatedQuad(const glm::vec2& position, float rotationRadians, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& color, float textureScale = 1.0f)
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, rotationRadians, size, subTexture, color, textureScale);
		}
		
		// === IMPL ===

		static void DrawRotatedQuad(const glm::vec3& position, float rotationRadians, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, float rotationRadians, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& color, float textureScale = 1.0f);

		// --- MASTER IMPLEMENTATION ---

		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f);
		static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, const glm::vec4& color, float textureScale = 1.0f);

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

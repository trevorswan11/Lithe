#pragma once

#include "Lithe/Core/Base.h"

#include "Lithe/Renderer/Camera.h"
#include "Lithe/Renderer/OrthographicCamera.h"
#include "Lithe/Renderer/EditorCamera.h"

#include "Lithe/Renderer/Texture.h"
#include "Lithe/Renderer/SubTexture2D.h"

#include "Lithe/Scene/Components.h"

namespace Lithe {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera); // TODO: remove
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void EndScene();
		static void Flush();

		static float GetLineWidth();
		static void SetLineWidth(float width);
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

		inline static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1)
		{
			DrawQuad(transform, (Ref<Texture2D>)nullptr, color, 1.0f, entityID);
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

		inline static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float textureScale = 1.0f, int entityID = -1)
		{
			DrawQuad(transform, texture, glm::vec4(1.0f), textureScale, entityID);
		}

		inline static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, float textureScale = 1.0f, int entityID = -1)
		{
			DrawQuad(transform, subTexture, glm::vec4(1.0f), textureScale, entityID);
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
	public:
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
	public:
		// --- MASTER IMPLEMENTATION ---

		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale = 1.0f, int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, const glm::vec4& color, float textureScale = 1.0f, int entityID = -1);
		
		static void DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);
		static void DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, int entityID = -1);
		static void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID = -1);
		static void DrawRect(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		
		// Component System
		static void DrawSpriteComponent(const glm::mat4& transform, SpriteRendererComponent& src, int entityID);
		static void DrawCircleComponent(const glm::mat4& transform, CircleRendererComponent& crc, int entityID);
	public:
		// --- Stats ---

		struct Stats
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			uint32_t CircleCount = 0;
			uint32_t LineCount = 0;

			uint32_t GetTotalVertexCount() const 
			{
				return LineCount * 2 + (QuadCount + CircleCount) * 4;
			};
			uint32_t GetTotalIndexCount() const
			{
				return (QuadCount + CircleCount) * 6;
			};
		};
		static void ResetStats();
		static Stats GetStats();
	};

}

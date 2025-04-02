#pragma once

#include "Lithe/Renderer/Texture.h"

#include <glm/glm.hpp>

namespace Lithe {

	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 });

		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }

		const glm::vec2 GetRawTexCoords() const { return m_RawCoords; }
		const glm::vec2 GetCellSize() const { return m_CellSize; }
		const glm::vec2 GetSpriteSize() const { return m_SpriteSize; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 });
	private:
		Ref<Texture2D> m_Texture;

		glm::vec2 m_TexCoords[4];

		glm::vec2 m_RawCoords;
		glm::vec2 m_CellSize;
		glm::vec2 m_SpriteSize;
	};

}

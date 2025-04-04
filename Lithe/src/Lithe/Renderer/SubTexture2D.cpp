#include "lipch.h"
#include "SubTexture2D.h"

namespace Lithe {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
		: m_Texture(texture), m_RawCoords(coords), m_CellSize(cellSize), m_SpriteSize(spriteSize)
	{
		glm::vec2 min = { (coords.x * cellSize.x) / texture->GetWidth(), (coords.y * cellSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	void SubTexture2D::RecalculateTexCoords()
	{
		glm::vec2 min = { (m_RawCoords.x * m_CellSize.x) / m_Texture->GetWidth(), (m_RawCoords.y * m_CellSize.y) / m_Texture->GetHeight() };
		glm::vec2 max = { ((m_RawCoords.x + m_SpriteSize.x) * m_CellSize.x) / m_Texture->GetWidth(), ((m_RawCoords.y + m_SpriteSize.y) * m_CellSize.y) / m_Texture->GetHeight() };
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		return CreateRef<SubTexture2D>(texture, coords, cellSize, spriteSize);
	}

}


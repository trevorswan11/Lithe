#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Renderer/Texture.h"

namespace Lithe {
	
	// Forward Declaration
	struct MSDFData;

	class Font
	{
	public:
		Font(const std::filesystem::path& filepath);
		~Font();

		Ref<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }
	private:
		MSDFData* m_Data;
		Ref<Texture2D> m_AtlasTexture;
	};

}


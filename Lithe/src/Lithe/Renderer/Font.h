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

		const MSDFData* GetMSDFData() const { return m_Data; }
		Ref<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }

		static Ref<Font> GetDefault();
	private:
		std::string GetCachePath(const std::filesystem::path& fontPath);
		bool TryLoadFromCache(const std::filesystem::path& filepath);
		void SaveToCache(const std::filesystem::path& filepath);
	private:
		MSDFData* m_Data;
		Ref<Texture2D> m_AtlasTexture;
	};

}


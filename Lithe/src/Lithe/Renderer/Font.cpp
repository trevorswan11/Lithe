#include "lipch.h"
#include "Font.h"

#include "Lithe/Core/Timer.h"

#include "Lithe/Renderer/MSDFData.h"

#undef INFINITE
#include <msdf-atlas-gen.h>
#include <FontGeometry.h>
#include <GlyphGeometry.h>


namespace Lithe {

	template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
	static Ref<Texture2D> CreateAndCacheAtlas(const std::string& fontName, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
		const msdf_atlas::FontGeometry& fontGeometry, uint32_t width, uint32_t height)
	{
		LI_PROFILE_FUNCTION();

		msdf_atlas::GeneratorAttributes attributes;
		attributes.config.overlapSupport = true;
		attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
		generator.setAttributes(attributes);
		generator.setThreadCount(8);
		generator.generate(glyphs.data(), (int)glyphs.size());

		msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();

		TextureSpecification spec;
		spec.Width = bitmap.width;
		spec.Height = bitmap.height;
		spec.Format = ImageFormat::RGB8;
		spec.GenerateMips = false;

		Ref<Texture2D> texture = Texture2D::Create(spec);
		texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * 3);
		return texture;
	}

	Font::Font(const std::filesystem::path& filepath)
		: m_Data(new MSDFData())
	{
		LI_PROFILE_FUNCTION();
#if 0
		std::string cachePath = GetCachePath(filepath);
		if (TryLoadFromCache(cachePath))
		{
			LI_CORE_INFO("Loaded font atlas from cache: {0}", cachePath);
			return;
		}
#endif

		Timer timer;
		msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
		LI_CORE_ASSERT(ft);

		std::string fileString = filepath.string();

		msdfgen::FontHandle* font = msdfgen::loadFont(ft, fileString.c_str());
		if (!font)
		{
			LI_CORE_ERROR("Failed to load font: {0}", fileString);
			return;
		}

		struct CharsetRange
		{
			uint32_t Begin, End;
		};

		// From imgui_draw.cpp
		static const CharsetRange charsetRanges[] =
		{
			{ 0x0020, 0x00FF }
		};

		msdf_atlas::Charset charset;
		for (CharsetRange range : charsetRanges)
		{
			for (uint32_t c = range.Begin; c <= range.End; c++)
				charset.add(c);
		}

		double fontScale = 1.0;
		m_Data->FontGeometry = msdf_atlas::FontGeometry(&m_Data->Glyphs);
		int glyphsLoaded = m_Data->FontGeometry.loadCharset(font, fontScale, charset);
		LI_CORE_INFO("Loading {0} glyphs from font (out of {1})", glyphsLoaded, charset.size());

		double emSize = 40.0;

		msdf_atlas::TightAtlasPacker atlasPacker;
		// atlasPacker.setDimensionsConstraint()
		atlasPacker.setPixelRange(2.0);
		atlasPacker.setMiterLimit(1.0);
		atlasPacker.setPadding(0);
		atlasPacker.setScale(emSize);
		int remaining = atlasPacker.pack(m_Data->Glyphs.data(), (int)m_Data->Glyphs.size());
		LI_CORE_ASSERT(remaining == 0);

		int width, height;
		atlasPacker.getDimensions(width, height);
		emSize = atlasPacker.getScale();

		#define DEFAULT_ANGLE_THRESHOLD 3.0
		#define LCG_MULTIPLIER 6364136223846793005ull
		#define LCG_INCREMENT 1442695040888963407ull
		#define THREAD_COUNT 8
		// if MSDF || MTSDF

		uint64_t coloringSeed = 0;
		bool expensiveColoring = false;
		if (expensiveColoring)
		{
			msdf_atlas::Workload([&glyphs = m_Data->Glyphs, &coloringSeed](int i, int threadNo) -> bool {
				unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
				glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
				return true;
				}, (int)m_Data->Glyphs.size()).finish(THREAD_COUNT);
		}
		else {
			unsigned long long glyphSeed = coloringSeed;
			for (msdf_atlas::GlyphGeometry& glyph : m_Data->Glyphs)
			{
				glyphSeed *= LCG_MULTIPLIER;
				glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
			}
		}

		m_AtlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>("Test", (float)emSize, m_Data->Glyphs, m_Data->FontGeometry, width, height);

		msdfgen::destroyFont(font);
		msdfgen::deinitializeFreetype(ft);

#if 0
		SaveToCache(cachePath);
#endif
		LI_CORE_WARN("Font {0} loaded in {1}", filepath.filename().string(), timer.ElapsedMillis());
	}

	Font::~Font()
	{
		delete m_Data;
	}


	Ref<Font> Font::GetDefault()
	{
		static Ref<Font> DefaultFont;
		if (!DefaultFont)
			DefaultFont = CreateRef<Font>("assets/fonts/opensans/static/OpenSans-Regular.ttf");

		return DefaultFont;
	}

	std::string Font::GetCachePath(const std::filesystem::path& fontPath)
	{
		std::filesystem::path cacheDir = "assets/cache/fonts";
		std::filesystem::create_directories(cacheDir);

		std::string filename = fontPath.stem().string() + ".msdfcache";
		return (cacheDir / filename).string();
	}

	// TODO: Font serialization/deserialization not functional

	bool Font::TryLoadFromCache(const std::filesystem::path& filepath)
	{
		LI_PROFILE_FUNCTION();

		if (!std::filesystem::exists(filepath))
			return false;

		std::ifstream in(filepath, std::ios::binary);
		if (!in.is_open())
			return false;

		int width, height, glyphCount;
		in.read((char*)&width, sizeof(int));
		in.read((char*)&height, sizeof(int));
		in.read((char*)&glyphCount, sizeof(int));

		std::vector<msdf_atlas::GlyphGeometry> glyphs(glyphCount);
		in.read((char*)glyphs.data(), glyphCount * sizeof(msdf_atlas::GlyphGeometry));

		size_t pixelDataSize = width * height * 3;
		std::vector<uint8_t> pixelData(pixelDataSize);
		in.read((char*)pixelData.data(), pixelDataSize);

		in.close();

		TextureSpecification spec;
		spec.Width = width;
		spec.Height = height;
		spec.Format = ImageFormat::RGB8;
		spec.GenerateMips = false;

		m_AtlasTexture = Texture2D::Create(spec);
		m_AtlasTexture->SetData(pixelData.data(), (uint32_t)pixelDataSize);

		m_Data->Glyphs = std::move(glyphs);

		return true;
	}

	void Font::SaveToCache(const std::filesystem::path& filepath)
	{
		LI_PROFILE_FUNCTION();
		
		LI_CORE_INFO("Saving font atlas to cache: {0}", filepath.string());

		int width = m_AtlasTexture->GetWidth();
		int height = m_AtlasTexture->GetHeight();
		int glyphCount = (int)m_Data->Glyphs.size();

		std::vector<uint8_t> pixelData(width * height * 3);
		m_AtlasTexture->ReadData(pixelData.data());

		std::ofstream out(filepath, std::ios::binary);
		out.write((char*)&width, sizeof(int));
		out.write((char*)&height, sizeof(int));
		out.write((char*)&glyphCount, sizeof(int));
		out.write((char*)m_Data->Glyphs.data(), glyphCount * sizeof(msdf_atlas::GlyphGeometry));
		out.write((char*)pixelData.data(), pixelData.size());
		out.close();
	}

}

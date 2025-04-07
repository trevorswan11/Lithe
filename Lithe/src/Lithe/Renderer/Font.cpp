#include "lipch.h"
#include "Font.h"

#include "Lithe/Core/Timer.h"

#undef INFINITE
#include <msdf-atlas-gen.h>
#include <FontGeometry.h>
#include <GlyphGeometry.h>

namespace Lithe {

	struct MSDFData
	{
		std::vector<msdf_atlas::GlyphGeometry> Glyphs;
		msdf_atlas::FontGeometry FontGeometry;
	};

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

		Timer timer;
		msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
		LI_CORE_ASSERT(ft);
		if (!ft)
		{
			LI_CORE_CRITICAL("Fatal error initializing freetype.");
			return;
		}
		std::string filestring = filepath.string();
		msdfgen::FontHandle* font = msdfgen::loadFont(ft, filestring.c_str());
		LI_CORE_ASSERT(font);
		if (!font)
		{
			LI_CORE_CRITICAL("Fatal error loading font: {0}", filestring);
			return;
		}

		struct CharsetRange
		{
			uint32_t Begin, End;
		};

		// imgui_draw.cpp
		static const CharsetRange charsetRanges[] =
		{
			{ 0x0020, 0x00FF }
		};
		msdf_atlas::Charset charset;
		for (CharsetRange cr : charsetRanges)
		{
			for (uint32_t c = cr.Begin; c <= cr.End; c++) charset.add(c);
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

		m_AtlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>("Test", (float)emSize, m_Data->Glyphs, m_Data->FontGeometry, width, height);

		msdfgen::destroyFont(font);
		msdfgen::deinitializeFreetype(ft);
		LI_CORE_WARN("Font generation took {0} ms", timer.ElapsedMillis());
	}

	Font::~Font()
	{
		delete m_Data;
	}

}

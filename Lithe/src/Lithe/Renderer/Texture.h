#pragma once

#include "Lithe/Core/Base.h"

namespace Lithe {

	enum class ImageFormat
	{
		None = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA32F
	};

	struct TextureSpecification
	{
		uint32_t Width = 1;
		uint32_t Height = 1;
		ImageFormat Format = ImageFormat::RGBA8;
		bool GenerateMips = true;
	};

	// ---- TEXTURE BASE CLASS ----

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual const TextureSpecification& GetSpecification() const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual const std::string& GetPath() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool IsLoaded() const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	// ---- TEXTURE 2D CLASS ----

	class Texture2D : public Texture
	{
	public:
		[[deprecated("Use Create(const TextureSpecification& specification) instead!")]]
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const TextureSpecification& specification);
		static Ref<Texture2D> Create(const std::string& path);
	};

}

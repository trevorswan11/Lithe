#pragma once

#include "Lithe/Core/Base.h"

namespace Lithe {

	// ---- TEXTURE BASE CLASS ----

	class LITHE_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		//virtual uint32_t GetFormat() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	// ---- TEXTURE 2D CLASS ----

	class LITHE_API Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};

}
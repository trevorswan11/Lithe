#pragma once

#include "Lithe/Renderer/Texture.h"

namespace Lithe {

	class VulkanTexture2D : public Texture2D
	{
	public:
		VulkanTexture2D(uint32_t width, uint32_t height);
		VulkanTexture2D(const TextureSpecification& specification);
		VulkanTexture2D(const std::string& path);
		virtual ~VulkanTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual const TextureSpecification& GetSpecification() const override { return m_TextureSpec; }

		virtual const std::string& GetPath() const override { return m_Path; }

		virtual void SetData(void* data, uint32_t size) override;
		virtual void ReadData(void* dst) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool IsLoaded() const override { return m_IsLoaded; }
		
		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((VulkanTexture2D&)other).m_RendererID;
		}
	private:
		TextureSpecification m_TextureSpec;
		std::string m_Path;
		bool m_IsLoaded = false;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		int m_InternalFormat, m_DataFormat;
	};

}

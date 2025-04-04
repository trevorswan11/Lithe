#pragma once

#include "Lithe/Renderer/Buffer.h"

namespace Lithe {

	// --------------------------- VERTEX BUFFER ---------------------------

	class HeadlessVertexBuffer : public VertexBuffer
	{
	public:
		HeadlessVertexBuffer(uint32_t size);
		HeadlessVertexBuffer(float* vertices, uint32_t size);
		virtual ~HeadlessVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	// --------------------------- INDEX BUFFER ---------------------------

	class HeadlessIndexBuffer : public IndexBuffer
	{
	public:
		HeadlessIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~HeadlessIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}

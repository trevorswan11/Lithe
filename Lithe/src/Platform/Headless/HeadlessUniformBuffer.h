#pragma once

#include "Lithe/Renderer/UniformBuffer.h"

namespace Lithe {

	class HeadlessUniformBuffer : public UniformBuffer
	{
		public:
			HeadlessUniformBuffer(uint32_t size, uint32_t binding);
			virtual ~HeadlessUniformBuffer();

			virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;
		private:
			uint32_t m_RendererID = 0;
	};

}

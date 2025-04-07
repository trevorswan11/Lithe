#pragma once

#include "Lithe/Core/Buffer.h"

namespace Lithe {

	class FileSystem
	{
	public:
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	};

}


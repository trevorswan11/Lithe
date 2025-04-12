#pragma once

#include "Lithe/Core/Buffer.h"
#include "Lithe/Project/Project.h"

namespace Lithe {

	class FileSystem
	{
	public:
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
		static std::filesystem::path MakeRelativePath(const std::filesystem::path& absPath, const std::filesystem::path& basePath = Project::GetAssetDirectory());
		static std::filesystem::path MakeAbsolutePath(const std::filesystem::path& relativePath, const std::filesystem::path& basePath = Project::GetAssetDirectory());
	};

}


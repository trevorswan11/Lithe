#include "lipch.h"
#include "FileSystem.h"

namespace Lithe {

	Buffer FileSystem::ReadFileBinary(const std::filesystem::path& filepath)
	{
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
		if (!stream) return {};

		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint64_t size = end - stream.tellg();

		if (size == 0) return {};

		Buffer buffer(size);
		stream.read(buffer.As<char>(), size);
		stream.close();

		return buffer;
	}

	std::filesystem::path FileSystem::MakeRelativePath(const std::filesystem::path& absPath, const std::filesystem::path& basePath)
	{
		namespace fs = std::filesystem;
		try {
			fs::path relative = fs::relative(absPath, basePath);
			return relative;
		}
		catch (const fs::filesystem_error& e) {
			LI_CORE_WARN("Failed to convert to relative path: {}", e.what());
			return absPath;
		}
	}

	std::filesystem::path FileSystem::MakeAbsolutePath(const std::filesystem::path& relativePath, const std::filesystem::path& basePath)
	{
		namespace fs = std::filesystem;
		try {
			fs::path absolute = fs::absolute(basePath / relativePath);
			return absolute.lexically_normal().string();
		}
		catch (const fs::filesystem_error& e) {
			LI_CORE_WARN("Failed to convert to absolute path: {}", e.what());
			return relativePath;
		}

	}

}

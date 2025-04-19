#pragma once

#include <string>
#include <optional>

namespace Lithe {

	class FileDialogs
	{
	public:
		// These return empty strings if cancelled!

		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);

		static void RevealInExplorer(const std::filesystem::path& filepath);
		static void OpenInExplorer(const std::filesystem::path& filepath);
	};

	class Time
	{
	public:
		static float GetTime();
	};

}

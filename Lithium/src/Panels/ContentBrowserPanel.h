#pragma once

#include <Lithe.h>

#include <filesystem>

namespace Lithe {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();

		void SetFontSize(float size) { m_FontSize = size; }

		std::string GetAndClearCurrentFile();
	private:
		std::filesystem::path m_BaseDirectory;
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_CurrentFile;

		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;

		float m_FontSize = ImGuiLayer::GetDefaultFontSize();
	};
}

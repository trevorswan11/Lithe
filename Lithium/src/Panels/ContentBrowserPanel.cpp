#include "lipch.h"
#include "ContentBrowserPanel.h"

#include "Lithe/Utils/PlatformUtils.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Lithe {

	ContentBrowserPanel::ContentBrowserPanel()
		: m_BaseDirectory(Project::GetAssetDirectory()), m_CurrentDirectory(m_BaseDirectory)
	{
		m_DirectoryIcon = Texture2D::Create("assets/resources/DirectoryIcon.png");
		m_FileIcon = Texture2D::Create("assets/resources/FileIcon.png");
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[(int)ImGuiFonts::Bold];
		
		ImGuiWindowClass window_class;
		window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
		ImGui::SetNextWindowClass(&window_class);
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
		ImGui::Begin("Content Browser", NULL, window_flags);

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			std::filesystem::path relativePath(path);
			std::string filenameString = relativePath.filename().string();

			ImGui::PushID(filenameString.c_str());
			Ref<Texture2D> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImTextureID textureId = reinterpret_cast<ImTextureID>(static_cast<uint64_t>(icon->GetRendererID()));
			ImGui::ImageButton(textureId, { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
			
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t), ImGuiCond_Once);
				ImGui::EndDragDropSource();
			}
			
			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
					m_CurrentDirectory /= path.filename();
				else
					m_CurrentFile = path;
			}
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Open in File Explorer"))
				{
					FileDialogs::RevealInExplorer(m_CurrentDirectory);
				}

				ImGui::EndPopup();
			}
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();
			ImGui::PopID();
		}

		ImGui::Columns(1);

		if (ImGui::BeginMenuBar())
		{
			ImGui::PushFont(boldFont);

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			if (ImGui::Button("."))
				LITHIUM_INFO("Current Directory: {0}", m_CurrentDirectory.string());
			if (ImGui::Button(".."))
			{
				if (m_CurrentDirectory != std::filesystem::path(m_BaseDirectory))
					m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
			ImGui::PopStyleColor();

			if (ImGui::BeginMenu("Display Settings"))
			{
				ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
				ImGui::SliderFloat("Padding", &padding, 0, 32);
				ImGui::EndMenu();
			}
			ImGui::PopFont();

			ImGui::Text("%s", m_CurrentDirectory.string().c_str());

			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	std::string ContentBrowserPanel::GetAndClearCurrentFile()
	{
		std::string path = m_CurrentFile.string();
		m_CurrentFile = std::filesystem::path();
		return path;
	}

}

#include "SceneHierarchyPanel.h"

#include "Lithe/Scene/Components.h"
#include "Lithe/Scripting/ScriptEngine.h"
#include "Lithe/UI/UI.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <glm/gtc/type_ptr.hpp>

#include <cstring>

namespace Lithe {

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
		m_SelectionContext = {};
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.view<entt::entity>().each([&](auto entityID)
			{
				Entity entity{ entityID, m_Context.get() };

				if (entity.HasComponent<RelationshipComponent>())
				{
					auto& rel = entity.GetComponent<RelationshipComponent>();
					if (rel.Parent == 0)
						DrawEntityNode(entity);
				}
				else
				{
					DrawEntityNode(entity);
				}
			});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		// Right-click on blank space
		if (!m_Context->IsRunning() && ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::SetSelectedEntity(Entity entity)
	{
		m_SelectionContext = entity;
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0)
			| ImGuiTreeNodeFlags_OpenOnArrow
			| ImGuiTreeNodeFlags_SpanAvailWidth;

		bool hasChildren = entity.HasComponent<RelationshipComponent>() && entity.GetComponent<RelationshipComponent>().FirstChild != 0;
		if (!hasChildren)
			flags |= ImGuiTreeNodeFlags_Leaf;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if (!m_Context->IsRunning() && ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete"))
				entityDeleted = true;
			if (ImGui::MenuItem("Duplicate"))
				m_Context->CloneEntity(entity);
			if (ImGui::MenuItem("Add Child"))
				m_Context->AttachEmptyChild(entity);

			ImGui::EndPopup();
		}

		if (opened)
		{
			if (hasChildren)
			{
				auto& rel = entity.GetComponent<RelationshipComponent>();
				UUID childUUID = rel.FirstChild;
				while (childUUID != 0)
				{
					Entity child = m_Context->GetEntityByUUID(childUUID);
					childUUID = child.GetComponent<RelationshipComponent>().NextSibling;
					DrawEntityNode(child);
				}
			}
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f, bool disableX = false, bool disableY = false, bool disableZ = false)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[(int)ImGuiFonts::Bold];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, disableX);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::PopItemFlag();

		ImGui::SameLine();

		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, disableY);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::PopItemFlag();

		ImGui::SameLine();

		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, disableZ);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::PopItemFlag();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction, bool removeable = true)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeable && removeComponent)
				entity.RemoveComponent<T>();
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, tag.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
				tag = std::string(buffer);

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("UUID: %s", std::to_string(entity.GetUUID()).c_str());
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			DisplayAddComponentEntry<CameraComponent>("Camera");
			DisplayAddComponentEntry<ScriptComponent>("Script");
			DisplayAddComponentEntry<SpriteRendererComponent>("Sprite Renderer");
			DisplayAddComponentEntry<RigidBody2DComponent>("RigidBody 2D");
			DisplayAddComponentEntry<BoxCollider2DComponent>("Box Collider 2D");
			DisplayAddComponentEntry<CircleRendererComponent>("Circle Renderer");
			DisplayAddComponentEntry<CircleCollider2DComponent>("Circle Collider 2D");
			DisplayAddComponentEntry<TextComponent>("Text Component");
			DisplayAddComponentEntry<AudioComponent>("Audio Component");

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		DrawComponent<TransformComponent>("Transform", entity, [&](auto& component)
			{
				bool isChild = false;
				if (entity.HasComponent<RelationshipComponent>())
					isChild = entity.GetComponent<RelationshipComponent>().Parent != 0;

				DrawVec3Control("Translation", component.Translation, 0.0f, 100.0f, isChild, isChild);
				glm::vec3 rotation = glm::degrees(component.Rotation);
				DrawVec3Control("Rotation", rotation);
				component.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", component.Scale, 1.0f);
			}, false
		);

		DrawComponent<CameraComponent>("Camera", entity, [](auto& component)
			{
				auto& camera = component.Camera;

				ImGui::Checkbox("Primary", &component.Primary);

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float perspectiveVerticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
						camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

					float perspectiveNear = camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &perspectiveNear))
						camera.SetPerspectiveNearClip(perspectiveNear);

					float perspectiveFar = camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &perspectiveFar))
						camera.SetPerspectiveFarClip(perspectiveFar);
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					float orthoNear = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthoNear))
						camera.SetOrthographicNearClip(orthoNear);

					float orthoFar = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
						camera.SetOrthographicFarClip(orthoFar);

					ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
				}
			}
		);

		DrawComponent<ScriptComponent>("Script", entity, [entity, scene = m_Context](auto& component) mutable
			{
				bool scriptClassExists = ScriptEngine::EntityClassExists(component.ClassName);

				static char buffer[64];
				strcpy_s(buffer, sizeof(buffer), component.ClassName.c_str());

				UI::ScopedStyleColor textColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.3f, 1.0f), !scriptClassExists);

				if (ImGui::InputText("Class", buffer, sizeof(buffer)))
				{
					component.ClassName = buffer;
					return;
				}

				// Fields
				bool sceneRunning = scene->IsRunning();
				if (sceneRunning)
				{
					Ref<ScriptInstance> scriptInstance = ScriptEngine::GetEntityScriptInstance(entity.GetUUID());
					if (scriptInstance)
					{
						const auto& fields = scriptInstance->GetScriptClass()->GetFields();
						for (const auto& [name, field] : fields)
						{
							if (field.Type == ScriptFieldType::Float)
							{
								float data = scriptInstance->GetFieldValue<float>(name);
								if (ImGui::DragFloat(name.c_str(), &data))
								{
									scriptInstance->SetFieldValue(name, data);
								}
							}
						}
					}
				}
				else
				{
					if (scriptClassExists)
					{
						Ref<ScriptClass> entityClass = ScriptEngine::GetEntityClass(component.ClassName);
						const auto& fields = entityClass->GetFields();

						auto& entityFields = ScriptEngine::GetScriptFieldMap(entity);
						for (const auto& [name, field] : fields)
						{
							// Field has been set in editor
							if (entityFields.find(name) != entityFields.end())
							{
								ScriptFieldInstance& scriptField = entityFields.at(name);

								// Display control to set it maybe
								if (field.Type == ScriptFieldType::Float)
								{
									float data = scriptField.GetValue<float>();
									if (ImGui::DragFloat(name.c_str(), &data))
										scriptField.SetValue(data);
								}
							}
							else
							{
								// Display control to set it maybe
								if (field.Type == ScriptFieldType::Float)
								{
									float data = 0.0f;
									if (ImGui::DragFloat(name.c_str(), &data))
									{
										ScriptFieldInstance& fieldInstance = entityFields[name];
										fieldInstance.Field = field;
										fieldInstance.SetValue(data);
									}
								}
							}
						}
					}
				}
			});

		DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [=](auto& component)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
				float buttonWidth = ImGui::GetContentRegionAvail().x / 2;
				if (ImGui::Button("Reset Texture", ImVec2(buttonWidth / 2, 0.0f)))
				{
					component.Texture = std::nullopt;
					component.SubTextureUsed = false;
				}
				ImGui::SameLine();
				ImGui::Button("Texture", ImVec2(buttonWidth / 1.4f, 0.0f));

				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* path = (const wchar_t*)payload->Data;
						std::filesystem::path texturePath(path);
						if (component.SubTextureUsed)
						{
							component.Texture = SubTexture2D::CreateFromCoords(
								Texture2D::Create(texturePath.string()),
								component.Coords,
								component.CellSize,
								component.SpriteSize
							);
							if (!std::get_if<Ref<SubTexture2D>>(&*component.Texture)->get()->GetTexture()->IsLoaded())
								component.Texture = std::nullopt;
						}
						else
						{
							component.Texture = Texture2D::Create(texturePath.string());
							if (!std::get_if<Ref<Texture2D>>(&*component.Texture)->get()->IsLoaded())
								component.Texture = std::nullopt;
						}
					}
					ImGui::EndDragDropTarget();
				}

				ImGui::SameLine();
				ImGui::Checkbox("SubTexture", &component.SubTextureUsed);
				if (component.Texture && component.SubTextureUsed)
				{
					if (auto subTexture2D = std::get_if<Ref<SubTexture2D>>(&*component.Texture))
					{
						if (ImGui::InputFloat2("Coords", glm::value_ptr(component.Coords), 3))
							subTexture2D->get()->SetRawTexCoords(component.Coords);
						if (ImGui::InputFloat2("Cell Size", glm::value_ptr(component.CellSize), 3))
							subTexture2D->get()->SetCellSize(component.CellSize);
						if (ImGui::InputFloat2("Sprite Size", glm::value_ptr(component.SpriteSize), 3))
							subTexture2D->get()->SetSpriteSize(component.SpriteSize);
						float width = ImGui::GetContentRegionAvail().x;
						if (ImGui::Button("Re-Render as Texture", ImVec2{ width, 0.0f }))
						{
							component.Texture = subTexture2D->get()->GetTexture();
							component.SubTextureUsed = false;
							component.TilingFactor = m_CachedTilingFactor;
						}
					}
				}

				if (component.Texture)
				{
					if (auto texture2D = std::get_if<Ref<Texture2D>>(&*component.Texture))
					{
						ImGui::SliderFloat("Tiling Factor", &component.TilingFactor, 0.1f, 100.0f);
						float width = ImGui::GetContentRegionAvail().x;
						if (ImGui::Button("Re-Render as Sub Texture", ImVec2{ width, 0.0f }))
						{
							component.Texture = SubTexture2D::CreateFromCoords(
								*texture2D,
								component.Coords,
								component.CellSize,
								component.SpriteSize
							);
							component.SubTextureUsed = true;
							m_CachedTilingFactor = component.TilingFactor;
							component.TilingFactor = 1.0f;
						}
					}
				}
			}
		);

		DrawComponent<CircleRendererComponent>("Circle Renderer", entity, [=](auto& component)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
				ImGui::DragFloat("Thickness", &component.Thickness, 0.025f, 0.0f, 1.0f);
				ImGui::DragFloat("Fade", &component.Fade, 0.00025f, 0.0f, 1.0f);

			}
		);
		

		DrawComponent<RigidBody2DComponent>("RigidBody 2D", entity, [=](auto& component)
			{
				const char* bodyTypeTypeStrings[] = { "Static", "Dynamic", "Kinematic"};
				const char* currentBodyTypeString = bodyTypeTypeStrings[(int)component.Type];
				if (ImGui::BeginCombo("Body Type", currentBodyTypeString))
				{
					for (int i = 0; i < 3; i++)
					{
						bool isSelected = currentBodyTypeString == bodyTypeTypeStrings[i];
						if (ImGui::Selectable(bodyTypeTypeStrings[i], isSelected))
						{
							currentBodyTypeString = bodyTypeTypeStrings[i];
							component.Type = (RigidBody2DComponent::BodyType)i;
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				ImGui::Checkbox("Fixed Rotation", &component.FixedRotation);
			}
		);

		DrawComponent<BoxCollider2DComponent>("Box Collider 2D", entity, [=](auto& component)
			{
				ImGui::DragFloat2("Offset", glm::value_ptr(component.Offset));
				ImGui::DragFloat2("Size", glm::value_ptr(component.Size));
				ImGui::DragFloat("Density", &component.Density, 0.01f, 0.0f, 1.0f);
				ImGui::DragFloat("Friction", &component.Friction, 0.01f, 0.0f, 1.0f);
				ImGui::DragFloat("Restituiton", &component.Restitution, 0.01f, 0.0f, 1.0f);
				ImGui::DragFloat("Restituiton Threshold", &component.RestitutionThreshold, 0.01f, 0.0f);
			}
		);

		DrawComponent<CircleCollider2DComponent>("Circle Collider 2D", entity, [=](auto& component)
			{
				ImGui::DragFloat2("Offset", glm::value_ptr(component.Offset));
				ImGui::DragFloat("Radius", &component.Radius);
				ImGui::DragFloat("Density", &component.Density, 0.01f, 0.0f, 1.0f);
				ImGui::DragFloat("Friction", &component.Friction, 0.01f, 0.0f, 1.0f);
				ImGui::DragFloat("Restituiton", &component.Restitution, 0.01f, 0.0f, 1.0f);
				ImGui::DragFloat("Restituiton Threshold", &component.RestitutionThreshold, 0.01f, 0.0f);
			}
		);

		DrawComponent<TextComponent>("Text Renderer", entity, [](auto& component)
			{
				ImGui::InputTextMultiline("Text String", &component.TextString);
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
				ImGui::DragFloat("Kerning", &component.Kerning, 0.025f);
				ImGui::DragFloat("Line Spacing", &component.LineSpacing, 0.025f);
			});

		DrawComponent<AudioComponent>("Audio", entity, [](auto& component)
			{
				float width = ImGui::GetContentRegionAvail().x;
				ImGui::Button("Audio", ImVec2(width / 1.4f, 0.0f));

				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* path = (const wchar_t*)payload->Data;
						std::filesystem::path audioPath(path);
						component.Path = audioPath.string();
					}
					ImGui::EndDragDropTarget();
				}
				ImGui::SameLine();
				
				ImGui::Checkbox("Play on start", &component.PlayOnStart);
				ImGui::DragFloat("Volume", &component.Volume, 0.01f, 0.0f, 1.0f);
				if (ImGui::Button("Clear Path", ImVec2(width / 1.4f, 0.0f)))
					component.Path = std::string();
				ImGui::SameLine();
				ImGui::Checkbox("Looping", &component.Looping);
				std::filesystem::path audioPath = std::filesystem::path(component.Path);
				ImGui::Text("Current path: %s", audioPath.filename().string().c_str());
			});
	}

	template<typename T>
	void SceneHierarchyPanel::DisplayAddComponentEntry(const std::string& entryName) {
		if (!m_SelectionContext.HasComponent<T>())
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				m_SelectionContext.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}

}

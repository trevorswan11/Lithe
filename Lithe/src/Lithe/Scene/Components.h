#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Core/UUID.h"
#include "Lithe/Core/AudioEngine.h"

#include "Lithe/Scene/SceneCamera.h"

#include "Lithe/Renderer/Texture.h"
#include "Lithe/Renderer/SubTexture2D.h"
#include "Lithe/Renderer/Font.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <optional>
#include <variant>

namespace Lithe {

	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
		
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		std::optional<std::variant<Ref<Texture2D>, Ref<SubTexture2D>>> Texture;
		float TilingFactor = 1.0f;
		glm::vec2 Coords{ 0.0f, 0.0f };
		glm::vec2 CellSize{ 1.0f, 1.0f };
		glm::vec2 SpriteSize{ 1.0f, 1.0f };
		bool SubTextureUsed = false;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CircleRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		float Radius = 0.5;
		float Thickness = 1.0f;
		float Fade = 0.005f;

		CircleRendererComponent() = default;
		CircleRendererComponent(const CircleRendererComponent&) = default;
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct TextComponent
	{
		std::string TextString;
		Ref<Font> FontAsset = Font::GetDefault();
		glm::vec4 Color{ 1.0f };
		float Kerning = 0.0f;
		float LineSpacing = 0.0f;
	};

	// Forward Declaration
	class ScriptableEntity;

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

	struct ScriptComponent
	{
		std::string ClassName;

		ScriptComponent() = default;
		ScriptComponent(const ScriptComponent&) = default;
	};

	// Physics
	
	struct RigidBody2DComponent
	{
		enum class BodyType { Static = 0, Dynamic, Kinematic };
		BodyType Type = BodyType::Static;
		bool FixedRotation = false;

		// Storage for runtime
		void* RuntimeBody = nullptr;

		RigidBody2DComponent() = default;
		RigidBody2DComponent(const RigidBody2DComponent&) = default;
	};

	struct BoxCollider2DComponent
	{
		glm::vec2 Offset = { 0.0f, 0.0f };
		glm::vec2 Size = { 0.5f, 0.5f };

		float Density = 1.0f;
		float Friction = 0.5;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		// Storage for runtime
		void* RuntimeBody = nullptr;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
	};

	struct CircleCollider2DComponent
	{
		glm::vec2 Offset = { 0.0f, 0.0f };
		float Radius = 0.5f;

		float Density = 1.0f;
		float Friction = 0.5;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		// Storage for runtime
		void* RuntimeBody = nullptr;

		CircleCollider2DComponent() = default;
		CircleCollider2DComponent(const CircleCollider2DComponent&) = default;
	};

	struct AudioComponent
	{
		std::string Path;
		Ref<Sound> Sound;
		float Volume = 1.0f;
		bool Looping = false;
		bool PlayOnStart = true;

		void Init()
		{
			if (Initialized) return;
			
			Sound = AudioEngine::CreateSound(Path.c_str(), Volume, Looping);
			if (Sound) Initialized = true;
		}

		AudioComponent() = default;
		AudioComponent(const AudioComponent&) = default;

		void Play() { Sound->Play(); Playing = true; }
		void Stop() { Sound->Stop(); Playing = false; }
		void SetVolume(float volume) { Sound->SetVolume(volume); Volume = volume; }
		void SetLooping(bool looping) { Sound->SetLooping(looping); Looping = looping; }
		bool IsValid() const { return Sound->IsValid(); }
		bool IsPlaying() const { return Playing; }
		bool IsInitialized() const { return Initialized; }
	private:
		bool Initialized = false;
		bool Playing = false;
	};

	struct RelationshipComponent
	{
		UUID Parent = 0;
		UUID FirstChild = 0;
		UUID NextSibling = 0;
		UUID PrevSibling = 0;

		RelationshipComponent() = default;
		RelationshipComponent(const RelationshipComponent&) = default;
	};


	template<typename... Component>
	struct ComponentGroup
	{};

	using AllComponents =
		ComponentGroup<TransformComponent, SpriteRendererComponent,
		CameraComponent, NativeScriptComponent, ScriptComponent,
		RigidBody2DComponent, CircleRendererComponent, BoxCollider2DComponent,
		CircleCollider2DComponent, TextComponent, AudioComponent, RelationshipComponent>;

}

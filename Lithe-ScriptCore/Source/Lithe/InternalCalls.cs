using System;
using System.Runtime.CompilerServices;
using static System.Runtime.CompilerServices.RuntimeHelpers;

namespace Lithe
{
    public static class InternalCalls
    {
		#region Logger
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Logger_LogTrace(string message);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Logger_LogInfo(string message);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Logger_LogWarn(string message);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Logger_LogError(string message);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Logger_LogCritical(string message);
		#endregion

		#region Entity
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool Entity_HasComponent(ulong entityID, Type componentType);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static ulong Entity_FindEntityByName(string name);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static object GetScriptInstance(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static ulong Entity_GetGlobalEntity();
		#endregion

		#region TransformComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_GetTranslation(ulong entityID, out Vec3 translation);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_SetTranslation(ulong entityID, ref Vec3 translation);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_GetRotation(ulong entityID, out Vec3 translation);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_SetRotation(ulong entityID, ref Vec3 translation);
		#endregion

		#region RigidBody2DComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void RigidBody2DComponent_ApplyLinearImpulse(ulong entityID, ref Vec2 impulse, ref Vec2 point, bool wake);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void RigidBody2DComponent_GetLinearVelocity(ulong entityID, out Vec2 linearVelocity);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static RigidBody2DComponent.BodyType RigidBody2DComponent_GetType(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void RigidBody2DComponent_SetType(ulong entityID, RigidBody2DComponent.BodyType type);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void RigidBody2DComponent_ApplyLinearImpulseToCenter(ulong entityID, ref Vec2 impulse, bool wake);
		#endregion

		#region TextComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static string TextComponent_GetText(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TextComponent_SetText(ulong entityID, string text);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TextComponent_GetColor(ulong entityID, out Vec4 color);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TextComponent_SetColor(ulong entityID, ref Vec4 color);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float TextComponent_GetKerning(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TextComponent_SetKerning(ulong entityID, float kerning);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float TextComponent_GetLineSpacing(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TextComponent_SetLineSpacing(ulong entityID, float lineSpacing);
		#endregion

		#region Input
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool Input_IsKeyDown(KeyCode keycode);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool Input_IsMouseDown(MouseCode mousecode);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Input_GetMousePosition(out Vec2 position);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Input_GetMouseWorldPosition(out Vec2 position);
		#endregion

		#region AudioComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static string AudioComponent_GetPath(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void AudioComponent_SetPath(ulong entityID, string path);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float AudioComponent_GetVolume(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void AudioComponent_SetVolume(ulong entityID, float volume);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool AudioComponent_GetLooping(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void AudioComponent_SetLooping(ulong entityID, bool looping);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool AudioComponent_GetPlayOnStart(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void AudioComponent_SetPlayOnStart(ulong entityID, bool playOnStart);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool AudioComponent_IsValid(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool AudioComponent_IsPlaying(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool AudioComponent_IsInitialized(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void AudioComponent_Init(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void AudioComponent_Play(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void AudioComponent_Stop(ulong entityID);
		#endregion

		#region SpriteRendererComponent
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_GetColor(ulong entityID, out Vec4 color);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_SetColor(ulong entityID, ref Vec4 color);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_EnableSubtexture(ulong entityID);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_DisableSubtexture(ulong entityID);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static bool SpriteRendererComponent_SubtextureUsed(ulong entityID);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_GetCoords(ulong entityID, out Vec2 coords);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_SetCoords(ulong entityID, ref Vec2 coords);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_GetCellSize(ulong entityID, out Vec2 cellSize);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_SetCellSize(ulong entityID, ref Vec2 cellSize);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_GetSpriteSize(ulong entityID, out Vec2 spriteSize);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_SetSpriteSize(ulong entityID, ref Vec2 spriteSize);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static string SpriteRendererComponent_GetTextureAbsolutePath(ulong entityID);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static string SpriteRendererComponent_GetTextureRelativePath(ulong entityID);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static void SpriteRendererComponent_SetTexturePath(ulong entityID, string path);
		[MethodImpl(MethodImplOptions.InternalCall)] 
		internal extern static bool SpriteRendererComponent_IsLoaded(ulong entityID);
		#endregion

		#region CircleRendererComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void CircleRendererComponent_GetColor(ulong entityID, out Vec4 outColor);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void CircleRendererComponent_SetColor(ulong entityID, ref Vec4 color);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float CircleRendererComponent_GetRadius(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void CircleRendererComponent_SetRadius(ulong entityID, float radius);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float CircleRendererComponent_GetThickness(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void CircleRendererComponent_SetThickness(ulong entityID, float thickness);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float CircleRendererComponent_GetFade(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void CircleRendererComponent_SetFade(ulong entityID, float fade);
		#endregion

		#region CameraComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern bool CameraComponent_GetPrimary(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CameraComponent_SetPrimary(ulong entityID, bool primary);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern bool CameraComponent_IsPrimary(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern bool CameraComponent_GetFixedAspectRatio(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CameraComponent_SetFixedAspectRatio(ulong entityID, bool value);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern bool CameraComponent_IsFixedAspectRatio(ulong entityID);
		#endregion

		#region BoxCollider2DComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void BoxCollider2DComponent_GetOffset(ulong entityID, out Vec2 offset);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void BoxCollider2DComponent_SetOffset(ulong entityID, ref Vec2 offset);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void BoxCollider2DComponent_GetSize(ulong entityID, out Vec2 size);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void BoxCollider2DComponent_SetSize(ulong entityID, ref Vec2 size);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float BoxCollider2DComponent_GetDensity(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void BoxCollider2DComponent_SetDensity(ulong entityID, float density);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float BoxCollider2DComponent_GetFriction(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void BoxCollider2DComponent_SetFriction(ulong entityID, float friction);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float BoxCollider2DComponent_GetRestitution(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void BoxCollider2DComponent_SetRestitution(ulong entityID, float restitution);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float BoxCollider2DComponent_GetRestitutionThreshold(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void BoxCollider2DComponent_SetRestitutionThreshold(ulong entityID, float threshold);
		#endregion

		#region CircleCollider2DComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CircleCollider2DComponent_GetOffset(ulong entityID, out Vec2 offset);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CircleCollider2DComponent_SetOffset(ulong entityID, ref Vec2 offset);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float CircleCollider2DComponent_GetRadius(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CircleCollider2DComponent_SetRadius(ulong entityID, float radius);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float CircleCollider2DComponent_GetDensity(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CircleCollider2DComponent_SetDensity(ulong entityID, float density);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float CircleCollider2DComponent_GetFriction(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CircleCollider2DComponent_SetFriction(ulong entityID, float friction);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float CircleCollider2DComponent_GetRestitution(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CircleCollider2DComponent_SetRestitution(ulong entityID, float restitution);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern float CircleCollider2DComponent_GetRestitutionThreshold(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal static extern void CircleCollider2DComponent_SetRestitutionThreshold(ulong entityID, float threshold);
		#endregion
	}
}

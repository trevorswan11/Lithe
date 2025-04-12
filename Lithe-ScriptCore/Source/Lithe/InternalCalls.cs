using System;
using System.Runtime.CompilerServices;
using static System.Runtime.CompilerServices.RuntimeHelpers;

namespace Lithe
{
    public static class InternalCalls
    {
		#region Entity
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool Entity_HasComponent(ulong entityID, Type componentType);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static ulong Entity_FindEntityByName(string name);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static object GetScriptInstance(ulong entityID);
		#endregion

		#region TransformComponent
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_GetTranslation(ulong entityID, out Vec3 translation);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_SetTranslation(ulong entityID, ref Vec3 translation);
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
	}
}

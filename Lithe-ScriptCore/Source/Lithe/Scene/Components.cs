using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lithe
{
	public abstract class Component
	{
		public Entity Entity { get; internal set; }
	}

	public class TransformComponent : Component
	{
		public Vec3 Translation
		{
			get
			{
				InternalCalls.TransformComponent_GetTranslation(Entity.ID, out Vec3 translation);
				return translation;
			}
			set
			{
				InternalCalls.TransformComponent_SetTranslation(Entity.ID, ref value);
			}
		}
	}

	public class RigidBody2DComponent : Component
	{
		public enum BodyType { Static = 0, Dynamic, Kinematic }

		public Vec2 LinearVelocity
		{
			get
			{
				InternalCalls.RigidBody2DComponent_GetLinearVelocity(Entity.ID, out Vec2 velocity);
				return velocity;
			}
		}

		public BodyType Type
		{
			get => InternalCalls.RigidBody2DComponent_GetType(Entity.ID);
			set => InternalCalls.RigidBody2DComponent_SetType(Entity.ID, value);
		}

		public void ApplyLinearImpulse(Vec2 impulse, Vec2 worldPosition, bool wake)
		{
			InternalCalls.RigidBody2DComponent_ApplyLinearImpulse(Entity.ID, ref impulse, ref worldPosition, wake);
		}

		public void ApplyLinearImpulse(Vec2 impulse, bool wake)
		{
			InternalCalls.RigidBody2DComponent_ApplyLinearImpulseToCenter(Entity.ID, ref impulse, wake);
		}

	}

	public class TextComponent : Component
	{

		public string Text
		{
			get => InternalCalls.TextComponent_GetText(Entity.ID);
			set => InternalCalls.TextComponent_SetText(Entity.ID, value);
		}

		public Vec4 Color
		{
			get
			{
				InternalCalls.TextComponent_GetColor(Entity.ID, out Vec4 color);
				return color;
			}

			set
			{
				InternalCalls.TextComponent_SetColor(Entity.ID, ref value);
			}
		}

		public float Kerning
		{
			get => InternalCalls.TextComponent_GetKerning(Entity.ID);
			set => InternalCalls.TextComponent_SetKerning(Entity.ID, value);
		}

		public float LineSpacing
		{
			get => InternalCalls.TextComponent_GetLineSpacing(Entity.ID);
			set => InternalCalls.TextComponent_SetLineSpacing(Entity.ID, value);
		}

	}

	public class AudioComponent : Component
	{
		public string AudioPath
		{
			get => InternalCalls.AudioComponent_GetPath(Entity.ID);
			set => InternalCalls.AudioComponent_SetPath(Entity.ID, value);
		}

		public float Volume
		{
			get => InternalCalls.AudioComponent_GetVolume(Entity.ID);
			set => InternalCalls.AudioComponent_SetVolume(Entity.ID, value);
		}

		public bool Looping
		{
			get => InternalCalls.AudioComponent_GetLooping(Entity.ID);
			set => InternalCalls.AudioComponent_SetLooping(Entity.ID, value);
		}

		public bool PlayOnStart
		{
			get => InternalCalls.AudioComponent_GetPlayOnStart(Entity.ID);
			set => InternalCalls.AudioComponent_SetPlayOnStart(Entity.ID, value);
		}

		public bool IsValid()
		{
			return InternalCalls.AudioComponent_IsValid(Entity.ID);
		}

		public bool IsPlaying()
		{
			return InternalCalls.AudioComponent_IsPlaying(Entity.ID);
		}

		public bool IsInitialized()
		{
			return InternalCalls.AudioComponent_IsInitialized(Entity.ID);
		}

		public void Init()
		{
			InternalCalls.AudioComponent_Init(Entity.ID);
		}

		public void Play()
		{
			InternalCalls.AudioComponent_Play(Entity.ID);
		}

		public void Stop()
		{
			InternalCalls.AudioComponent_Stop(Entity.ID);
		}
	}

}

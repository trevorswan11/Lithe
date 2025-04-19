using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lithe
{

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

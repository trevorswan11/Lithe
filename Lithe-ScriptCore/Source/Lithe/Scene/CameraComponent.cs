using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lithe
{
	public class CameraComponent : Component
	{
		public bool Primary
		{
			get => InternalCalls.CameraComponent_GetPrimary(Entity.ID);
			set => InternalCalls.CameraComponent_SetPrimary(Entity.ID, value);
		}

		public bool IsPrimary => InternalCalls.CameraComponent_IsPrimary(Entity.ID);

		public bool FixedAspectRatio
		{
			get => InternalCalls.CameraComponent_GetFixedAspectRatio(Entity.ID);
			set => InternalCalls.CameraComponent_SetFixedAspectRatio(Entity.ID, value);
		}

		public bool IsFixedAspectRatio => InternalCalls.CameraComponent_IsFixedAspectRatio(Entity.ID);
	}
}

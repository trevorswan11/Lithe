using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lithe
{

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

		public Vec3 Rotation
		{
			get
			{
				InternalCalls.TransformComponent_GetRotation(Entity.ID, out Vec3 rotation);
				return rotation;
			}
			set
			{
				InternalCalls.TransformComponent_SetRotation(Entity.ID, ref value);
			}
		}

		public void SetTranslationXY(Vec2 translation)
		{
			Vec3 vecTranslation = new Vec3(translation, Translation.z);
			InternalCalls.TransformComponent_SetTranslation(Entity.ID, ref vecTranslation);
		}

		public void SetRoationX(float rotationX)
		{
			Vec3 vecRotation = new Vec3(rotationX, Rotation.y, Rotation.z);
			InternalCalls.TransformComponent_SetRotation(Entity.ID, ref vecRotation);
		}

		public void SetRoationY(float rotationY)
		{
			Vec3 vecRotation = new Vec3(Rotation.x, rotationY, Rotation.z);
			InternalCalls.TransformComponent_SetRotation(Entity.ID, ref vecRotation);
		}
		public void SetRoationZ(float rotationZ)
		{
			Vec3 vecRotation = new Vec3(Rotation.XY, rotationZ);
			InternalCalls.TransformComponent_SetRotation(Entity.ID, ref vecRotation);
		}
	}

}

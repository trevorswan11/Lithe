﻿using System;
using System.Runtime.CompilerServices;

namespace Lithe
{
	public class Entity
	{
		protected Entity() { ID = 0; }

		internal Entity(ulong id)
		{
			ID = id;
		}

		public readonly ulong ID;

		public Vec3 Translation
		{
			get
			{
				InternalCalls.TransformComponent_GetTranslation(ID, out Vec3 result);
				return result;
			}
			set
			{
				InternalCalls.TransformComponent_SetTranslation(ID, ref value);
			}
		}

		public Vec3 Rotation
		{
			get
			{
				InternalCalls.TransformComponent_GetRotation(ID, out Vec3 result);
				return result;
			}
			set
			{
				InternalCalls.TransformComponent_SetRotation(ID, ref value);
			}
		}

		public bool HasComponent<T>() where T : Component, new()
		{
			Type componentType = typeof(T);
			return InternalCalls.Entity_HasComponent(ID, componentType);
		}

		public T GetComponent<T>() where T : Component, new()
		{
			if (!HasComponent<T>())
				return null;

			T component = new T() { Entity = this };
			return component;
		}

		public Entity FindEntityByName(string name)
		{
			ulong entityID = InternalCalls.Entity_FindEntityByName(name);
			if (entityID == 0)
				return null;

			return new Entity(entityID);
		}

		public bool IsHovered()
		{
			ulong selectedID = InternalCalls.Entity_GetGlobalEntity();
			if (selectedID == 0) return false;

			return selectedID == ID;
		}

		public T As<T>() where T : Entity, new()
		{
			object instance = InternalCalls.GetScriptInstance(ID);
			return instance as T;
		}

	}

	public abstract class Component
	{
		public Entity Entity { get; internal set; }
	}

}

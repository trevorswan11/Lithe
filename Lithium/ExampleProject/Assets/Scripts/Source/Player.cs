﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Lithe;

namespace Example
{
	public class Player : Entity
	{
		private TransformComponent m_Transform;
		private RigidBody2DComponent m_RigidBody;

		public float Speed;
		public float Time = 0.0f;

		void OnCreate()
		{
			Console.WriteLine($"Player.OnCreate - {ID}");

			m_Transform = GetComponent<TransformComponent>();
			m_RigidBody = GetComponent<RigidBody2DComponent>();
		}

		void OnUpdate(float ts)
		{
			Time += ts;

			float speed = Speed;
			Vec3 velocity = Vec3.Zero;

			if (Input.IsKeyDown(KeyCode.W))
				velocity.y = 1.0f;
			else if (Input.IsKeyDown(KeyCode.S))
				velocity.y = -1.0f;

			if (Input.IsKeyDown(KeyCode.A))
				velocity.x = -1.0f;
			else if (Input.IsKeyDown(KeyCode.D))
				velocity.x = 1.0f;

			Entity cameraEntity = FindEntityByName("Camera");
			if (cameraEntity != null)
			{
				Camera camera = cameraEntity.As<Camera>();

				if (Input.IsKeyDown(KeyCode.Q))
					camera.DistanceFromPlayer += speed * 2.0f * ts;
				else if (Input.IsKeyDown(KeyCode.E))
					camera.DistanceFromPlayer -= speed * 2.0f * ts;
			}

			velocity *= speed * ts;

			m_RigidBody.ApplyLinearImpulse(velocity.XY, true);
		}

	}
}

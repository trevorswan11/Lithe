using System;

namespace Lithe
{

	public struct Vec3
    {
		public float x, y, z;

		public static Vec3 Zero => new Vec3(0.0f);

		public Vec3(float scalar)
		{
			x = scalar;
			y = scalar;
			z = scalar;
		}

		public Vec3(float x_in, float y_in, float z_in)
		{
			x = x_in;
			y = y_in;
			z = z_in;
		}

		public Vec3(Vec2 xy, float z_in)
		{
			x = xy.x;
			y = xy.y;
			z = z_in;
		}

		public Vec2 XY
		{
			get => new Vec2(x, y);
			set
			{
				x = value.x;
				y = value.y;
			}
		}

		public static Vec3 operator +(Vec3 a, Vec3 b)
		{
			return new Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
		}

		public static Vec3 operator *(Vec3 vector, float scalar)
		{
			return new Vec3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
		}

		public float Magnitude()
		{
			return (float)Math.Sqrt(x * x + y * y + z * z);
		}

		public float MagnitudeSquared()
		{
			return x * x + y * y + z * z;
		}
	}

}

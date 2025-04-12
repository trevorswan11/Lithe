using System;

namespace Lithe
{

	public struct Vec4
    {
		public float x, y, z, w;

		public static Vec4 Zero => new Vec4(0.0f);

		public Vec4(float scalar)
		{
			x = scalar;
			y = scalar;
			z = scalar;
			w = scalar;
		}

		public Vec4(float x_in, float y_in, float z_in, float w_in)
		{
			x = x_in;
			y = y_in;
			z = z_in;
			w = w_in;
		}

		public Vec4(Vec3 xyz, float w_in)
		{
			x = xyz.x;
			y = xyz.y;
			z = xyz.z;
			w = w_in;
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

		public Vec3 XYZ
		{
			get => new Vec3(x, y, z);
			set
			{
				x = value.x;
				y = value.y;
				z = value.z;
			}
		}

		public static Vec4 operator +(Vec4 a, Vec4 b)
		{
			return new Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
		}

		public static Vec4 operator *(Vec4 vector, float scalar)
		{
			return new Vec4(vector.x * scalar, vector.y * scalar, vector.z * scalar, vector.w * scalar);
		}

		public float Magnitude()
		{
			return (float)Math.Sqrt(x * x + y * y + z * z + w * w);
		}

		public float MagnitudeSquared()
		{
			return x * x + y * y + z * z + w * w;
		}
	}

}

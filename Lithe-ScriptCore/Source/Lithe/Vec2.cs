using System;

namespace Lithe
{

    public struct Vec2
    {
		public float x, y;

		public static Vec2 Zero => new Vec2(0.0f);

		public Vec2(float scalar)
		{
			x = scalar;
			y = scalar;
		}

		public Vec2(float x_in, float y_in)
		{
			x = x_in;
			y = y_in;
		}

		public static Vec2 operator +(Vec2 a, Vec2 b)
		{
			return new Vec2(a.x + b.x, a.y + b.y);
		}

		public static Vec2 operator *(Vec2 vector, float scalar)
		{
			return new Vec2(vector.x * scalar, vector.y * scalar);
		}

		public float Magnitude()
		{
			return (float)Math.Sqrt(x * x + y * y);
		}

		public float MagnitudeSquared()
		{
			return x * x + y * y;
		}
	}

}

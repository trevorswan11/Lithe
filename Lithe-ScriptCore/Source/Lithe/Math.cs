using System;

namespace Lithe
{
	// Lithe Math Library
	public static class LML
	{
		public static readonly float PI = 3.1415926535897931f;
		public static readonly float E = 2.7182818284590451f;

		public static T Clamp<T>(this T val, T min, T max) where T : IComparable<T>
		{
			if (val.CompareTo(min) < 0) return min;
			else if (val.CompareTo(max) > 0) return max;
			else return val;
		}

		public static float Lerp(float a, float b, float t) => a + (b - a) * Clamp<float>(t, 0f, 1f);

		public static float LerpAngle(float a, float b, float t)
		{
			float delta = ((b - a + PI) % (2 * PI)) - PI;
			return a + delta * Clamp<float>(t, 0f, 1f);
		}
	}
}

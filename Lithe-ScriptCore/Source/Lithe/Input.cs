namespace Lithe
{

	public class Input
	{
		public static bool IsKeyDown(KeyCode keycode)
		{
			return InternalCalls.Input_IsKeyDown(keycode);
		}

		public static bool IsMouseDown(MouseCode mousecode)
		{
			return InternalCalls.Input_IsMouseDown(mousecode);
		}

		public static Vec2 GetMousePos()
		{
			InternalCalls.Input_GetMousePosition(out Vec2 vector);
			return vector;
		}

		public static Vec2 GetMouseWorldPos()
		{
			InternalCalls.Input_GetMouseWorldPosition(out Vec2 vector);
			return vector;
		}
	}

}


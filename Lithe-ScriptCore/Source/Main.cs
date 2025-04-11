using System;

namespace Lithe {
	
	public class Main
	{
		public float FloatVar { get; set; }
		public Main()
		{
			Console.WriteLine("C# says: Main Constructor");
		}

		public void PrintMessage()
		{
			Console.WriteLine("C# says: Hello World from C#");
		}
		public void PrintInt(int i)
		{
			Console.WriteLine($"C# says: {i}");
		}

		public void PrintInts(int i, int j)
		{
			Console.WriteLine($"C# says: {i}, {j}");
		}

		public void PrintCustomMessage(string message)
		{
			Console.WriteLine($"C# says: {message}");
		}
	}

}

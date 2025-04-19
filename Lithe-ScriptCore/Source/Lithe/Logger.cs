namespace Lithe
{
    public class Logger
    {
		public static void LogTrace(string message)
		{
			InternalCalls.Logger_LogTrace(message);
		}

		public static void LogInfo(string message)
		{
			InternalCalls.Logger_LogInfo(message);
		}

		public static void LogWarn(string message)
		{
			InternalCalls.Logger_LogWarn(message);
		}

		public static void LogError(string message)
		{
			InternalCalls.Logger_LogError(message);
		}

		public static void LogCritical(string message)
		{
			InternalCalls.Logger_LogCritical(message);
		}
	}
}

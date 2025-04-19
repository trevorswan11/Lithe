#pragma once

namespace Lithe {

	static void Logger_LogTrace(MonoString* string)
	{
		std::string str = ScriptEngine::CreateString(string);
		LI_TRACE(str);
	}

	static void Logger_LogInfo(MonoString* string)
	{
		std::string str = ScriptEngine::CreateString(string);
		LI_INFO(str);
	}

	static void Logger_LogWarn(MonoString* string)
	{
		std::string str = ScriptEngine::CreateString(string);
		LI_WARN(str);
	}

	static void Logger_LogError(MonoString* string)
	{
		std::string str = ScriptEngine::CreateString(string);
		LI_ERROR(str);
	}

	static void Logger_LogCritical(MonoString* string)
	{
		std::string str = ScriptEngine::CreateString(string);
		LI_CRITICAL(str);
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}

	static bool Input_IsMouseDown(MouseCode mousecode)
	{
		return Input::IsMouseButtonPressed(mousecode);
	}

	static void Input_GetMousePosition(glm::vec2* outPosition)
	{
		auto [x, y] = Input::GetMousePos();
		*outPosition = glm::vec2(x, y);
	}

	static void Input_GetMouseWorldPosition(glm::vec2* outPosition)
	{
		*outPosition = ScriptEngine::GetMouseWorldPosition();
	}

}

#pragma once

#include "Lithe/Core/Base.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

namespace Lithe {

	// Handles applciation wide logging
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetEditorLogger() { return s_EditorLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_EditorLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

inline std::string format_as(const glm::vec2& vector)
{
	return glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

inline std::string format_as(const glm::vec3& vector)
{
	return glm::to_string(vector);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternio)
{
	return os << glm::to_string(quaternio);
}

inline std::string format_as(const glm::vec4& vector)
{
	return glm::to_string(vector);
}

// Core log macros

#define LI_CORE_TRACE(...)		::Lithe::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LI_CORE_INFO(...)		::Lithe::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LI_CORE_WARN(...)		::Lithe::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LI_CORE_ERROR(...)		::Lithe::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LI_CORE_CRITICAL(...)	::Lithe::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Editor macros
#define LITHIUM_TRACE(...)		::Lithe::Log::GetEditorLogger()->trace(__VA_ARGS__)
#define LITHIUM_INFO(...)		::Lithe::Log::GetEditorLogger()->info(__VA_ARGS__)
#define LITHIUM_WARN(...)		::Lithe::Log::GetEditorLogger()->warn(__VA_ARGS__)
#define LITHIUM_ERROR(...)		::Lithe::Log::GetEditorLogger()->error(__VA_ARGS__)
#define LITHIUM_CRITICAL(...)	::Lithe::Log::GetEditorLogger()->critical(__VA_ARGS__)

// Client log macros

#define LI_TRACE(...)			::Lithe::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LI_INFO(...)			::Lithe::Log::GetClientLogger()->info(__VA_ARGS__)
#define LI_WARN(...)			::Lithe::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LI_ERROR(...)			::Lithe::Log::GetClientLogger()->error(__VA_ARGS__)
#define LI_CRITICAL(...)		::Lithe::Log::GetClientLogger()->critical(__VA_ARGS__)

// if dist build -- Prevents core logging
// 
//#define LI_CORE_TRACE(...)
//#define LI_CORE_INFO(...)
//#define LI_CORE_WARN(...)
//#define LI_CORE_ERROR(...)
//#define LI_CORE_CRITICAL(...)

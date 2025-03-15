#pragma once

#include "Lithe/Core/Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Lithe {

	// Handles applciation wide logging
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros

#define LI_CORE_TRACE(...)		::Lithe::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LI_CORE_INFO(...)		::Lithe::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LI_CORE_WARN(...)		::Lithe::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LI_CORE_ERROR(...)		::Lithe::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LI_CORE_CRTITICAL(...)	::Lithe::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros

#define LI_TRACE(...)			::Lithe::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LI_INFO(...)			::Lithe::Log::GetClientLogger()->info(__VA_ARGS__)
#define LI_WARN(...)			::Lithe::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LI_ERROR(...)			::Lithe::Log::GetClientLogger()->error(__VA_ARGS__)
#define LI_CRTITICAL(...)		::Lithe::Log::GetClientLogger()->critical(__VA_ARGS__)

// if dist build -- Prevents core logging
// 
//#define LI_CORE_TRACE(...)
//#define LI_CORE_INFO(...)
//#define LI_CORE_WARN(...)
//#define LI_CORE_ERROR(...)
//#define LI_CORE_CRTITICAL(...)
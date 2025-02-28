#include "lipch.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Lithe {

	// CORE: Handles all logging events; names LITHE
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	// CLEINT: Handles all logging events; named APP
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	// Initializes the Loggers with their format specifiers and names
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("LITHE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}
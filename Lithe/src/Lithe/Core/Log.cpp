#include "lipch.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Lithe {

	// CORE: Handles all logging events; named LITHE
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	// EDITOR: Handles all logging events; named LITHIUM
	std::shared_ptr<spdlog::logger> Log::s_EditorLogger;
	// CLEINT: Handles all logging events; named APP
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	// Initializes the Loggers with their format specifiers and names
	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("LitheOutput.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_CoreLogger = std::make_shared<spdlog::logger>("LITHE", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_EditorLogger = std::make_shared<spdlog::logger>("LITHIUM", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_EditorLogger);
		s_EditorLogger->set_level(spdlog::level::trace);
		s_EditorLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}

}

#include "tlpch.hh"
#include "log.hh"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace triangl::log {

	std::shared_ptr<spdlog::logger> g_engine_logger = nullptr,
									g_editor_logger = nullptr,
									g_client_logger = nullptr;

	void init()
	{
		spdlog::sink_ptr sinks[] =
		{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("triangl.log", true)
		};

		sinks[0]->set_pattern("%^[%T] %n: %v%$");
		sinks[1]->set_pattern("[%T] (%l) %n: %v");

		auto create_logger = [sinks](const std::string& name) -> std::shared_ptr<spdlog::logger>
		{
			std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
			spdlog::register_logger(logger);

			logger->set_level(spdlog::level::trace);
			logger->flush_on(spdlog::level::trace);

			return logger;
		};

		g_engine_logger = create_logger("ENGINE");
		g_editor_logger = create_logger("EDITOR");
		g_client_logger = create_logger("CLIENT");
	}

	void test_build_post_fatal()
	{
		std::cout << "  -> " STRING_NOTIFY_TERMINATION_POST_FATAL_LOG "\n";
		std::exit(EXIT_FAILURE);
	}

}

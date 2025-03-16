#ifndef TRIANGL_CORE_LOG_HH
#define TRIANGL_CORE_LOG_HH 1

#include "misc/msgdialog.hh"

#define SPDLOG_FMT_EXTERNAL    1
#define FMT_HEADER_ONLY        1
#define FMT_DEPRECATED_OSTREAM 1

#define SPDLOG_LEVEL_NAMES { "trace", "dbg", "inf", "warn", "err", "fatal", "off" }
#define SPDLOG_SHORT_LEVEL_NAMES { "T", "D", "I", "W", "E", "F", "O" }

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#define STRING_NOTIFY_TERMINATION_POST_FATAL_LOG "The application will be aborted due to that."

namespace triangl::log {

	extern std::shared_ptr<spdlog::logger> engine_logger,
										   editor_logger,
										   client_logger;

	void init();
	void test_build_post_fatal();

	template <typename... Args>
	void dist_err_or_fatal_log(bool fatal, const std::string& sender, fmt::string_view fmt, Args&&... args)
	{
		dialog_spec spec =
		{
			fatal ? "Fatal error!" : "Runtime error!",
			fmt::vformat(fmt, fmt::make_format_args(args...)) + std::string("\n\nLogged by: ") + sender,
			dialog_buttonset::ok,
			dialog_icon::error
		};

		if (fatal)
		{
			spec.content +=  + "\n" STRING_NOTIFY_TERMINATION_POST_FATAL_LOG;
		}

		std::unique_ptr<message_dialog> dialog = message_dialog::create(spec);
		dialog->create_and_wait();

		if (fatal)
		{
			std::exit(EXIT_FAILURE);
		}
	}

}

template <typename O, typename T, glm::qualifier Q>
inline O& operator<<(const O& stream, const glm::qua<T, Q>& qua)
{
	return stream << glm::to_string(qua);
}

template <typename O, glm::length_t L, typename T, glm::qualifier Q>
inline O& operator<<(const O& stream, const glm::vec<L, T, Q>& vec)
{
	return stream << glm::to_string(vec);
}

template <typename O, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline O& operator<<(const O& stream, const glm::mat<C, R, T, Q>& mat)
{
	return stream << glm::to_string(mat);
}

#ifdef TL_TEST_BUILD
	#define TL_LOGGER_TRACE(logger, ...)   logger->trace(__VA_ARGS__)
	#define TL_LOGGER_INFO(logger, ...)    logger->info(__VA_ARGS__)
	#define TL_LOGGER_WARN(logger, ...)    logger->warn(__VA_ARGS__)
	#define TL_LOGGER_ERROR(logger, ...)   logger->error(__VA_ARGS__)
	#define TL_LOGGER_FATAL(logger, ...) { logger->critical(__VA_ARGS__); ::triangl::log::test_build_post_fatal(); }
#else
	#define TL_LOGGER_TRACE(logger, ...)
	#define TL_LOGGER_INFO(logger, ...)
	#define TL_LOGGER_WARN(logger, ...)
	#define TL_LOGGER_ERROR(logger, ...)   ::triangl::log::dist_err_or_fatal_log(false, logger->name(), __VA_ARGS__)
	#define TL_LOGGER_FATAL(logger, ...)   ::triangl::log::dist_err_or_fatal_log(true,  logger->name(), __VA_ARGS__)
#endif

#define TL_CORE_TRACE(...)   TL_LOGGER_TRACE(::triangl::log::engine_logger, __VA_ARGS__)
#define TL_CORE_INFO(...)    TL_LOGGER_INFO (::triangl::log::engine_logger, __VA_ARGS__)
#define TL_CORE_WARN(...)    TL_LOGGER_WARN (::triangl::log::engine_logger, __VA_ARGS__)
#define TL_CORE_ERROR(...)   TL_LOGGER_ERROR(::triangl::log::engine_logger, __VA_ARGS__)
#define TL_CORE_FATAL(...)   TL_LOGGER_FATAL(::triangl::log::engine_logger, __VA_ARGS__)

#define TL_EDITOR_TRACE(...) TL_LOGGER_TRACE(::triangl::log::editor_logger, __VA_ARGS__)
#define TL_EDITOR_INFO(...)  TL_LOGGER_INFO (::triangl::log::editor_logger, __VA_ARGS__)
#define TL_EDITOR_WARN(...)  TL_LOGGER_WARN (::triangl::log::editor_logger, __VA_ARGS__)
#define TL_EDITOR_ERROR(...) TL_LOGGER_ERROR(::triangl::log::editor_logger, __VA_ARGS__)
#define TL_EDITOR_FATAL(...) TL_LOGGER_FATAL(::triangl::log::editor_logger, __VA_ARGS__)

#define TL_CLIENT_TRACE(...) TL_LOGGER_TRACE(::triangl::log::client_logger, __VA_ARGS__)
#define TL_CLIENT_INFO(...)  TL_LOGGER_INFO (::triangl::log::client_logger, __VA_ARGS__)
#define TL_CLIENT_WARN(...)  TL_LOGGER_WARN (::triangl::log::client_logger, __VA_ARGS__)
#define TL_CLIENT_ERROR(...) TL_LOGGER_ERROR(::triangl::log::client_logger, __VA_ARGS__)
#define TL_CLIENT_FATAL(...) TL_LOGGER_FATAL(::triangl::log::client_logger, __VA_ARGS__)

#define TL_TRACE(...)        TL_CLIENT_TRACE(__VA_ARGS__)
#define TL_INFO(...)         TL_CLIENT_INFO (__VA_ARGS__)
#define TL_WARN(...)         TL_CLIENT_WARN (__VA_ARGS__)
#define TL_ERROR(...)        TL_CLIENT_ERROR(__VA_ARGS__)
#define TL_FATAL(...)        TL_CLIENT_FATAL(__VA_ARGS__)

#endif

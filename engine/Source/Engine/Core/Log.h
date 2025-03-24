#pragma once

#include "Misc/MessageDialog.h"

#define SPDLOG_FMT_EXTERNAL    1
#define FMT_HEADER_ONLY        1
#define FMT_DEPRECATED_OSTREAM 1

#define SPDLOG_LEVEL_NAMES { "trace", "debug", "info", "warn", "error", "fatal", "off" }
#define SPDLOG_SHORT_LEVEL_NAMES { "T", "D", "I", "W", "E", "F", "O" }

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#define STRING_NOTIFY_TERMINATION_POST_FATAL_LOG "The application will be aborted due to that."

namespace Triangl
{
	class Log
	{
	public:
		static void Init();
		static void TestBuild_PostFatal();

		template <typename... Args>
		static void Shipping_ErrorOrFatalLog(bool fatal, const std::string& sender, fmt::string_view format, Args&&... args)
		{
			DialogSpecification spec =
			{
				fatal ? "Fatal error!" : "Runtime error!",
				fmt::vformat(format, fmt::make_format_args(args...)) + std::string("\n\nLogged by: ") + sender,
				DialogButtonset::Ok,
				DialogIcon::Error
			};
		
			if (fatal)
			{
				spec.Content += "\n" STRING_NOTIFY_TERMINATION_POST_FATAL_LOG;
			}
		
			Scope<MessageDialog> dialog = MessageDialog::New(spec);
			dialog->CreateAndWait();
		
			if (fatal)
			{
				std::exit(EXIT_FAILURE);
			}
		}

		static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		static std::shared_ptr<spdlog::logger>& GetEditorLogger() { return s_EditorLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		inline static std::shared_ptr<spdlog::logger> s_EngineLogger;
		inline static std::shared_ptr<spdlog::logger> s_EditorLogger;
		inline static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

template <typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(const OStream& stream, const glm::qua<T, Q>& quat)
{
	return stream << glm::to_string(quat);
}

template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(const OStream& stream, const glm::vec<L, T, Q>& vector)
{
	return stream << glm::to_string(vector);
}

template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(const OStream& stream, const glm::mat<C, R, T, Q>& matrix)
{
	return stream << glm::to_string(matrix);
}

#define TL_LOGGER_TRACE(logger, ...)     { logger->trace(__VA_ARGS__); }
#define TL_LOGGER_INFO(logger, ...)      { logger->info(__VA_ARGS__); }
#define TL_LOGGER_WARN(logger, ...)      { logger->warn(__VA_ARGS__); }

#ifdef TL_TEST_BUILD
	#define TL_LOGGER_ERROR(logger, ...) { logger->error(__VA_ARGS__); }
	#define TL_LOGGER_FATAL(logger, ...) { logger->critical(__VA_ARGS__); ::Triangl::Log::TestBuild_PostFatal(); }
#else
	#define TL_LOGGER_ERROR(logger, ...) { logger->error(__VA_ARGS__); ::Triangl::Log::Shipping_ErrorOrFatalLog(false, logger->name(), __VA_ARGS__); }
	#define TL_LOGGER_FATAL(logger, ...) { logger->critical(__VA_ARGS__); ::Triangl::Log::Shipping_ErrorOrFatalLog(true, logger->name(), __VA_ARGS__); }
#endif

#define TL_CORE_TRACE(...)   TL_LOGGER_TRACE(::Triangl::Log::GetEngineLogger(), __VA_ARGS__)
#define TL_CORE_INFO(...)    TL_LOGGER_INFO (::Triangl::Log::GetEngineLogger(), __VA_ARGS__)
#define TL_CORE_WARN(...)    TL_LOGGER_WARN (::Triangl::Log::GetEngineLogger(), __VA_ARGS__)
#define TL_CORE_ERROR(...)   TL_LOGGER_ERROR(::Triangl::Log::GetEngineLogger(), __VA_ARGS__)
#define TL_CORE_FATAL(...)   TL_LOGGER_FATAL(::Triangl::Log::GetEngineLogger(), __VA_ARGS__)

#define TL_EDITOR_TRACE(...) TL_LOGGER_TRACE(::Triangl::Log::GetEditorLogger(), __VA_ARGS__)
#define TL_EDITOR_INFO(...)  TL_LOGGER_INFO (::Triangl::Log::GetEditorLogger(), __VA_ARGS__)
#define TL_EDITOR_WARN(...)  TL_LOGGER_WARN (::Triangl::Log::GetEditorLogger(), __VA_ARGS__)
#define TL_EDITOR_ERROR(...) TL_LOGGER_ERROR(::Triangl::Log::GetEditorLogger(), __VA_ARGS__)
#define TL_EDITOR_FATAL(...) TL_LOGGER_FATAL(::Triangl::Log::GetEditorLogger(), __VA_ARGS__)

#define TL_CLIENT_TRACE(...) TL_LOGGER_TRACE(::Triangl::Log::GetClientLogger(), __VA_ARGS__)
#define TL_CLIENT_INFO(...)  TL_LOGGER_INFO (::Triangl::Log::GetClientLogger(), __VA_ARGS__)
#define TL_CLIENT_WARN(...)  TL_LOGGER_WARN (::Triangl::Log::GetClientLogger(), __VA_ARGS__)
#define TL_CLIENT_ERROR(...) TL_LOGGER_ERROR(::Triangl::Log::GetClientLogger(), __VA_ARGS__)
#define TL_CLIENT_FATAL(...) TL_LOGGER_FATAL(::Triangl::Log::GetClientLogger(), __VA_ARGS__)

#define TL_TRACE(...)        TL_CLIENT_TRACE(__VA_ARGS__)
#define TL_INFO(...)         TL_CLIENT_INFO (__VA_ARGS__)
#define TL_WARN(...)         TL_CLIENT_WARN (__VA_ARGS__)
#define TL_ERROR(...)        TL_CLIENT_ERROR(__VA_ARGS__)
#define TL_FATAL(...)        TL_CLIENT_FATAL(__VA_ARGS__)

#pragma once

#include "core/mlist_lib.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>
#include <string>
namespace mlist
{
	class MLIST_API Log
	{
	private:
		/* Logger for core information and debug */
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		/* Logger for general log, such as messages etc */
		static std::shared_ptr<spdlog::logger> s_UserLogger;
	public:

		/* Return a empty string if no errors ocurr */
		static std::string Init();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetUserLogger() { return s_UserLogger; }
	};
}

/* Core logger macros */
#if defined MLIST_DEBUG || defined MLIST_SHOW_DEBUG_MESSAGE //TODO: Add this define as a build config option

/* Use for logging on debug mode */
#define MLIST_CORE_LOG_DEBUG(...) ::mlist::Log::GetCoreLogger()->debug(__VA_ARGS__)
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_ERROR(...) ::mlist::Log::GetCoreLogger()->error(__VA_ARGS__)
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_WARN(...) ::mlist::Log::GetCoreLogger()->warn(__VA_ARGS__)
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_INFO(...) ::mlist::Log::GetCoreLogger()->info(__VA_ARGS__)
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_TRACE(...) ::mlist::Log::GetCoreLogger()->trace(__VA_ARGS__)
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_FATAL(...) ::mlist::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#else // Dist or Release mode

/* Use for logging on debug mode */
#define MLIST_CORE_LOG_DEBUG(...) 
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_ERROR(...) 
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_WARN(...) 
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_INFO(...) 
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_TRACE(...) 
/* Use for logging on debug mode */
#define MLIST_CORE_LOG_FATAL(...) 

#endif

/* User logger macros */

/* Use for logging on console */
#define MLIST_USER_LOG_DEBUG(...) ::mlist::Log::GetUserLogger()->debug(__VA_ARGS__)
/* Use for logging on console */
#define MLIST_USER_LOG_ERROR(...) ::mlist::Log::GetUserLogger()->error(__VA_ARGS__)
/* Use for logging on console */
#define MLIST_USER_LOG_WARN(...) ::mlist::Log::GetUserLogger()->warn(__VA_ARGS__)
/* Use for logging on console */
#define MLIST_USER_LOG_INFO(...) ::mlist::Log::GetUserLogger()->info(__VA_ARGS__)
/* Use for logging on console */
#define MLIST_USER_LOG_TRACE(...) ::mlist::Log::GetUserLogger()->trace(__VA_ARGS__)
/* Use for logging on console */
#define MLIST_USER_LOG_FATAL(...) ::mlist::Log::GetUserLogger()->fatal(__VA_ARGS__)

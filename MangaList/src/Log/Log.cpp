#include "core/pch.h"
#include "Log.h"

namespace mlist
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_UserLogger;

    std::string Log::Init()
    {
        try
        {
            s_CoreLogger = spdlog::stdout_color_mt("Debug");
            s_CoreLogger->set_pattern("%^[%T] %n: %v%$");
            s_CoreLogger->set_level(spdlog::level::trace);

            s_UserLogger = spdlog::stdout_color_mt("User");
            s_UserLogger->set_pattern("%v%$");
            s_UserLogger->set_level(spdlog::level::trace);

            return std::string();
        }
        catch (const std::exception& ex)
        {
            return ex.what();
        }
    }
}
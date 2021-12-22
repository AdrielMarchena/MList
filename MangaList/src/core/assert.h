#pragma once

#include "Log/Log.h"
#include "debugbreak.h"

#if defined MLIST_DEBUG

#define MLIST_CORE_ASSERT_LOG(expression,...) if (!(expression)) { MLIST_CORE_LOG_WARN(__VA_ARGS__); debug_break(); }
#define MLIST_CORE_ASSERT(expression) if (!(expression)) { debug_break(); }

#else

#define MLIST_CORE_ASSERT_LOG(expression,...)
#define MLIST_CORE_ASSERT(expression) 

#endif
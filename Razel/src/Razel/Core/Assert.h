#pragma once

#include "Razel/Core/Base.h"
#include "Razel/Core/Log.h"
#include <filesystem>

#ifdef RZ_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define RZ_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { RZ##type##ERROR(msg, __VA_ARGS__); RZ_DEBUGBREAK(); } }
#define RZ_INTERNAL_ASSERT_WITH_MSG(type, check, ...) RZ_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define RZ_INTERNAL_ASSERT_NO_MSG(type, check) RZ_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", RZ_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define RZ_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define RZ_INTERNAL_ASSERT_GET_MACRO(...) RZ_EXPAND_MACRO( RZ_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, RZ_INTERNAL_ASSERT_WITH_MSG, RZ_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define RZ_ASSERT(...) RZ_EXPAND_MACRO( RZ_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define RZ_CORE_ASSERT(...) RZ_EXPAND_MACRO( RZ_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define RZ_ASSERT(...)
#define RZ_CORE_ASSERT(...)
#endif
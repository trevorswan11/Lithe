#pragma once

#include "Lithe/Core/Base.h"
#include "Lithe/Core/Log.h"
#include <filesystem>

#ifdef LI_ENABLE_ASSERTS
	
	#define LI_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LI##type##ERROR(msg, __VA_ARGS__); LI_DEBUGBREAK(); } }
	#define LI_INTERNAL_ASSERT_WITH_MSG(type, check, ...) LI_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define LI_INTERNAL_ASSERT_NO_MSG(type, check) LI_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", LI_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
	
	#define LI_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define LI_INTERNAL_ASSERT_GET_MACRO(...) LI_EXPAND_MACRO( LI_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LI_INTERNAL_ASSERT_WITH_MSG, LI_INTERNAL_ASSERT_NO_MSG) )
	
	#define LI_ASSERT(...) LI_EXPAND_MACRO( LI_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define LI_CORE_ASSERT(...) LI_EXPAND_MACRO( LI_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define LI_ASSERT(...)
	#define LI_CORE_ASSERT(...)
#endif

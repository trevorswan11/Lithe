#pragma once

#include <memory>

#ifdef LI_PLATFORM_WINDOWS
#if LI_DYNAMIC_LINK
	#ifdef LI_BUILD_DLL
		// Macro for exports in core engine
		#define LITHE_API __declspec(dllexport)
	#else
		// Macro for imports in derived applications
		#define LITHE_API __declspec(dllimport)
	#endif
#else
	#define LITHE_API
#endif
#else
	// For now, Lithe will only be built to support windows
	#error Lithe only supports Windows.
#endif

// Assertions if enabled, specified in premake for debug only
#ifdef LI_DEBUG
	#define LI_ENABLE_ASSERTS
#endif


#ifdef LI_ENABLE_ASSERTS
	// CLIENT: Breaks debugging (fatal error) if condition is not met, prints qualifying information
	#define LI_ASSERT(x, ...) { if(!(x)) { LI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	// CORE: Breaks debugging (fatal error) if condition is not met, prints qualifying information
	#define LI_CORE_ASSERT(x, ...) { if(!(x)) { LI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	// CLIENT: Does nothing without LI_ENABLE_ASSERTS
	#define LI_ASSERT(x, ...)
	// CORE: Does nothing without LI_ENABLE_ASSERTS
	#define LI_CORE_ASSERT(x, ...)
#endif

// Creates a bitmask with only the x-th bit set
#define BIT(x) (1 << x)

#define LI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Lithe {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
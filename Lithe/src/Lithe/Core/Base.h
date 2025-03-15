#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define LI_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define LI_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define LI_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define LI_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define LI_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif // End of platform detection

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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
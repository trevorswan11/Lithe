#pragma once

#include "ClientConfig.h"
#include "Lithe/Core/PlatformDetection.h"

#include <memory>

// Assertions if enabled, specified in premake for debug only
#ifdef LI_DEBUG
	#if defined(LI_PLATFORM_WINDOWS)
		#define LI_DEBUGBREAK() __debugbreak()
	#elif defined(LI_PLATFORM_LINUX)
		#include <signal.h>
		#define LI_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define LI_ENABLE_ASSERTS
#else
	#define LI_DEBUGBREAK()
#endif

#ifndef CLIENT_DISABLE_PROFILE
	#define LI_PROFILE
#endif

#define LI_EXPAND_MACRO(x) x
#define LI_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define LI_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define CONCAT(x, y) x ## y

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

	template<typename T>
	using WeakRef = std::weak_ptr<T>;

}

#include "Lithe/Core/Log.h"
#include "Lithe/Core/Assert.h"

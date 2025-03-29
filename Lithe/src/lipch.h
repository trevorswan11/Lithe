#pragma once

#include "Lithe/Core/PlatformDetection.h"

#ifdef LI_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

// Include this header file as the first import in any project cpp files!

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <cstdint>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Lithe/Core/Log.h"

#include "Lithe/Debug/Instrumentor.h"

#ifdef LI_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

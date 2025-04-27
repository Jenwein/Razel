#pragma once

#include "Razel/Core/PlatformDetection.h"

#ifdef RZ_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif

#include <iostream>
#include <ostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Razel/Core/Base.h"
#include "Razel/Core/Log.h"
#include "Razel/Debug/Instrumentor.h"

#ifdef RZ_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
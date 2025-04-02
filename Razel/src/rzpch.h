#pragma once

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

#include "Razel/Core/Log.h"
#include "Razel/Debug/Instrumentor.h"

#ifdef RZ_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
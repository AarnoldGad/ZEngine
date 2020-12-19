#ifndef ZE_INCLUDE
#define ZE_INCLUDE

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include <functional>
#include <filesystem>
#include <utility>
#include <memory>
#include <algorithm>
#include <ctime>
#include <cstdint>

#include <vector>
#include <stack>
#include <deque>
#include <array>
#include <map>

#ifdef _WIN32
	#include <Windows.h>
#endif

#include <zengine/Abstract/Singleton.hpp>

#include <zengine/Core/Application.hpp>

#include <zengine/Common/Logger.hpp>
#include <zengine/Common/Date.hpp>
#include <zengine/Common/Time.hpp>
#include <zengine/Common/Clock.hpp>
#include <zengine/Common/tee.hpp>

#include <zengine/Event/Event.hpp>
#include <zengine/Event/EventBus.hpp>
#include <zengine/Event/EventHandler.hpp>

#endif // ZE_INCLUDE

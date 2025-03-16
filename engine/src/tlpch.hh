#ifndef TRIANGL_PCH_HH
#define TRIANGL_PCH_HH 1

#include "core/assert.hh"

#ifdef TL_PLATFORM_WINDOWS
	#include <Windows.h>
#elif defined TL_PLATFORM_LINUX
	#include <linux/limits.h>
	#include <unistd.h>
#endif

#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <functional>
#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <random>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <regex>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <any>
#include <new>

#endif

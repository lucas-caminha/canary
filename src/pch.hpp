/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
 */

#ifndef SRC_PCH_HPP_
#define SRC_PCH_HPP_

// Definitions should be global.
#include "utils/definitions.h"
#include "utils/simd.hpp"

#include <bitset>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <forward_list>
#include <list>
#include <map>
#include <random>
#include <ranges>
#include <regex>
#include <set>
#include <queue>
#include <vector>
#include <variant>

#include <asio.hpp>
#include <fmt/chrono.h>
#include <gmp.h>
#include <json/json.h>
#if __has_include("luajit/lua.hpp")
	#include <luajit/lua.hpp>
#else
	#include <lua.hpp>
#endif
#include <magic_enum.hpp>
#include <mio/mmap.hpp>
#include <mysql.h>
#include <mysql/errmsg.h>
#include <spdlog/spdlog.h>
#include <parallel_hashmap/phmap.h>
#include <pugixml.hpp>
#include <zlib.h>
// HTTP connection library
#if __linux
	#include <dpp/dpp.h>
#elif defined(WIN32)
	#include <wininet.h>
#endif

#endif // SRC_PCH_HPP_

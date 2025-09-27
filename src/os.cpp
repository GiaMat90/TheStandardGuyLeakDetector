/*
 * Copyright 2025 Giacomo Matzeu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "os.h"

#ifdef _WIN32
#include <windows.h>
constexpr std::size_t max_path_size{ MAX_PATH };
#else
#include <climits>	// PATH_MAX
#include <unistd.h>
constexpr std::size_t max_path_size{ PATH_MAX };
#endif

#include <chrono>
#include <time.h> // ctime_s

std::string os::get_current_dir() {
	char buffer[max_path_size];
#ifdef _WIN32
	return GetCurrentDirectoryA(sizeof(buffer), buffer) > 0 ? std::string(buffer) : std::string("");
#else
	return std::string(getcwd(buffer, sizeof(buffer)));
#endif
}

std::string os::get_now_time() {
	/*
	* ctime_s return a date in this format
	* "DDD MMM  D HH:MM:SS YYYY\n"
	* That has 26 characters including the null terminator
	*/
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buffer[26];
#if _WIN32
	ctime_s(buffer, sizeof(buffer), &now);
#else
	ctime_r(&now, buffer);
#endif
	return std::string(buffer);
}

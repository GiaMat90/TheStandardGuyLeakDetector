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
#pragma once

#include <cstddef> // std::size_t

struct where {
	const char* file;
	const char* function;
	int line;
	where(const char* f, const char* fun, int l) : file(f), function(fun), line(l) {};
};

class allocation {
private:
	using pointer_t = void*;
	using file_t = const char*;
	using function_t = const char*;
	using line_t = std::size_t;
public:
	allocation();
	allocation(pointer_t p);
	allocation(std::size_t s, pointer_t p);
	allocation(const where& w, std::size_t s, pointer_t p);
	allocation(const where& w);
	allocation(std::size_t s);
	~allocation() = default;
public:
	inline std::size_t size() const noexcept { return m_size; };
	inline file_t get_file() const noexcept { return m_file; };
	inline function_t get_function() const noexcept { return m_function; };
	inline line_t get_line() const noexcept { return m_line; };
public:
	inline bool operator==(const allocation& other) const noexcept {
		return (m_ptr == other.m_ptr);
	}
public:
	void free();
private:
	pointer_t m_ptr{ nullptr };
	file_t m_file{};
	function_t m_function{};
	line_t m_line{};
	std::size_t m_size{};
};
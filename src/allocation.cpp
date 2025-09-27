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
#include "allocation.h"
#include <cstdlib>	// std::free
 
allocation::allocation() : 
	m_file(), m_function(), m_line(), m_ptr{nullptr}, m_size() {};
allocation::allocation(pointer_t p) : 
	m_file(), m_function(), m_line(), m_ptr(p), m_size() {};
allocation::allocation(std::size_t s, pointer_t p) : 
	m_file(), m_function(), m_line(), m_ptr(p), m_size(s) {};
allocation::allocation(const where& w, std::size_t s, pointer_t p) :
	m_file(w.file), m_function(w.function), m_line(w.line), m_ptr(p), m_size(s) {};
allocation::allocation(const where& w) :
	m_file(w.file), m_function(w.function), m_line(w.line), m_ptr{ nullptr }, m_size() {};
allocation::allocation(std::size_t s) :
	m_file(), m_function(), m_line(), m_ptr{ nullptr }, m_size(s) {};

void allocation::free() {
	if (m_ptr) {
		std::free(m_ptr);
		m_ptr = nullptr;
	}
}
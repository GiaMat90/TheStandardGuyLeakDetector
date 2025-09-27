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
#include "detektor.h"
#include "os.h"
#include <cstdio>
#include <fstream>

static detektor g_detektor;

detektor::detektor() {	
	printf("Leak Detektor is awake and ready");
};
detektor::~detektor() {
	save_report();
	print_report();
	clean_memory();
};

void detektor::print_report() const noexcept {
	if (std::size_t size = m_allocations.size() > std::size_t(0u)) {
		printf("Detektor found %zu leakes\n", m_allocations.size());
		printf("|\tBytes\t|\tFile\t|\tLine\t|\tFunction\t|\n");
		std::size_t lost_bytes{};
		auto current = m_allocations.begin();
		while (current) {
			lost_bytes += current->data.size();			
			printf("| %zu |", current->data.size());
			if (current->data.get_file()) {
				printf(" %s |", current->data.get_file());
			}
			else {
				printf(" NA |");
			}
			if (current->data.get_line() > 0) {
				printf(" %zu |", current->data.get_line());
			}
			else {
				printf(" NA |");
			}
			if (current->data.get_function()) {
				printf(" %s |", current->data.get_function());
			}
			else {
				printf(" NA |");
			}
			printf("\n");
			current = current->next;
		}
		printf("Bytes losted: %zu\n", lost_bytes);
	}
	else {
		printf("No memory leaked\n");
	}
	printf("Detektor goes to sleep\n");
}

void detektor::save_report() const noexcept {
	std::fstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit); // enabling exceptions
	try {
		std::string file_path = os::get_current_dir() + "/detektor_report.txt";
		file.open(file_path, std::ios::out | std::ios::trunc); // overwrite existing file
		if (file.is_open()) {
			file << "Detektor report generated " << os::get_now_time(); // no need new line, ctime_s add it
			if (std::size_t size = m_allocations.size() > std::size_t(0u)) {
				file << "Detektor found " << m_allocations.size() << " leakes\n";
				file << "|\tBytes\t|\tFile\t|\tLine\t|\tFunction\t|\n";
				std::size_t lost_bytes{};
				auto current = m_allocations.begin();
				while (current) {
					lost_bytes += current->data.size();
					file << "| " << current->data.size() << " | ";
					if (current->data.get_file()) {
						file << current->data.get_file() << " | ";
					}
					else {
						file << " | ";
					}
					if (current->data.get_line() > 0) {
						file << current->data.get_line() << " | ";
					}
					else {
						file << " | ";
					}
					if (current->data.get_function()) {
						file << current->data.get_function() << " | ";
					}
					else {
						file << " | ";
					}
					file << std::endl;
					current = current->next;
				}
				file << "Bytes losted: " << lost_bytes << "\n";
			}
			else {
				file << "No memory leaked\n";
			}
			file.close();
		}
	}
	catch (std::exception& e) {
		printf("Detektor: exception saving report %s", e.what());
	}
	catch (...) {
		printf("Detektor: error saving report");
	}
}

void detektor::clean_memory() const noexcept {
	auto current = m_allocations.begin();
	while (current) {
		current->data.free();
		current = current->next;
	}
}

/* placement new with file, function and line info */
void* operator new(std::size_t n, const where& w) {
	if (void* p = std::malloc(n)) {
		g_detektor.add_allocation(w, n, p);
		return p;
	}
	else {
		throw std::bad_alloc();
	}
}
void* operator new[](std::size_t n, const where& w) {
	if (void* p = std::malloc(n)) {
		g_detektor.add_allocation(w, n, p);
		return p;
	}
	else {
		throw std::bad_alloc();
	}
}
/* regular new operators */
void* operator new(std::size_t n) {
	if (void* p = std::malloc(n)) {
		g_detektor.add_allocation(n, p);
		return p;
	}
	else {
		throw std::bad_alloc();
	}
}
void* operator new[](std::size_t n) {
	if (void* p = std::malloc(n)) {
		g_detektor.add_allocation(n, p);
		return p;
	}
	else {
		throw std::bad_alloc();
	}
}
/* Placement delete */
void operator delete (void* p, std::size_t, where) noexcept {
	if (p) {
		g_detektor.add_deallocation(p);
		std::free(p);
	}
}
void operator delete[](void* p, std::size_t, where) noexcept {
	if (p) {
		g_detektor.add_deallocation(p);
		std::free(p);
	}
}
/* Regular delete */
void operator delete (void* p, std::size_t) noexcept {
	if (p) {
		g_detektor.add_deallocation(p);
		std::free(p);
	}
}
void operator delete[](void* p, std::size_t) noexcept {
	if (p) {
		g_detektor.add_deallocation(p);
		std::free(p);
	}
}
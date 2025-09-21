#include "detektor.h"
#include <iostream>
#include <print>
#include <fstream>
#include <filesystem>

detektor::detektor() {	
	std::print("Leak Detektor is awake and ready");
};
detektor::~detektor() {
	save_report();
	print_report();
	clean_memory();
};

void detektor::print_report() const noexcept {
	if (std::size_t size = m_allocations.size() > std::size_t(0u)) {
		std::print("Detektor found {} leakes\n", m_allocations.size());
		std::print("|\tBytes\t|\tFile\t|\tLine\t|\tFunction\t|\n");
		std::size_t lost_bytes{};
		auto current = m_allocations.begin();
		while (current) {
			lost_bytes += current->data.size();			
			std::cout << "| " << current->data.size() << " |";
			if (current->data.get_file()) {
				std::cout << current->data.get_file() << " |";
			}
			else {
				std::cout << " |";
			}
			if (current->data.get_line() > 0) {
				std::cout << current->data.get_line() << " |";
			}
			else {
				std::cout << " | ";
			}
			if (current->data.get_function()) {
				std::cout << current->data.get_function() << " |";
			}
			else {
				std::cout << " |";
			}
			std::cout << std::endl;
			current = current->next;
		}
		std::print("Bytes losted: {}\n", lost_bytes);
	}
	else {
		std::print("No memory leaked\n");
	}
	std::print("Detektor goes to sleep\n");
}

void detektor::save_report() const noexcept {
	std::fstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit); // enabling exceptions
	try {
		std::filesystem::path file_path = std::filesystem::current_path() / "detektor_report.txt";
		file.open(file_path, std::ios::out | std::ios::trunc); // overwrite existing file
		if (file.is_open()) {
			/*
			* ctime_s return a date in this format
			* "DDD MMM  D HH:MM:SS YYYY\n"
			* That has 26 characters including the null terminator
			*/
			auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			char buffer[26];
			ctime_s(buffer, sizeof(buffer), &now);
			file << "Detektor report generated " << buffer; // no need new line, ctime_s add it
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
		std::print("Detektor: exception saving report {}", e.what());
	}
	catch (...) {
		std::print("Detektor: error saving report");
	}
}

void detektor::clean_memory() const noexcept {
	auto current = m_allocations.begin();
	while (current) {
		current->data.free();
		current = current->next;
	}
}
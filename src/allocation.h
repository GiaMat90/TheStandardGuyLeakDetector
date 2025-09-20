#pragma once

#include <cstddef> // std::size_t

class allocation {
	using pointer_t = void*;
	using file_t = const char*;
	using line_t = int;
public:
	allocation();
	allocation(pointer_t p);
	allocation(std::size_t s, pointer_t p);
	allocation(file_t f, line_t l, std::size_t s, pointer_t p);
	allocation(file_t f, line_t l);
	allocation(std::size_t s);
public:
	inline std::size_t size() const noexcept { return m_size; };
public:
	inline bool operator==(const allocation& other) const noexcept {
		return (m_ptr == other.m_ptr);
	}
private:
	pointer_t m_ptr{ nullptr };
	file_t m_file{};
	line_t m_line{};
	std::size_t m_size{};
};
#pragma once

#include "allocation.h"
#include "linked_list.h"
#include <mutex>

class detektor {
public:
	detektor();
	~detektor();
	template <typename...Args>
	inline void add_allocation(Args... args) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_allocations.push(args...);
	};
	inline void add_deallocation(void* p) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_allocations.remove(p);
	};
private:
	void save_report() const noexcept;
	void print_report() const noexcept;
	void clean_memory() const noexcept;
private:
	linked_list<allocation> m_allocations;
	std::mutex m_mutex;
};

/* placement new with file, function and line info */
void* operator new(std::size_t n, const where& w);
void* operator new[](std::size_t n, const where& w);
/* regular new operators */
void* operator new(std::size_t n);
void* operator new[](std::size_t n);
/* Placement delete */
void operator delete (void* p, std::size_t, where) noexcept;
void operator delete[](void* p, std::size_t, where) noexcept;
/* Regular delete */
void operator delete (void* p, std::size_t) noexcept;
void operator delete[](void* p, std::size_t) noexcept;


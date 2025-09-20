#pragma once

#include "allocation.h"
#include "linked_list.h"

class detektor {
public:
	detektor();
	~detektor();
	template <typename...Args>
	inline void add_allocation(Args... args) {
		m_allocations.push(args...);
	};
	inline void add_deallocation(void* p) {
		m_allocations.remove(p);
	};
private:
	linked_list<allocation> m_allocations;
};

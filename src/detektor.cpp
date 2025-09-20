#include "detektor.h"
#include <tsg/io.h> // tsg::print

detektor::detektor() {
	tsg::print("detektor::constructor called");
};
detektor::~detektor() {
	tsg::print("tsld report:");
	if (std::size_t size = m_allocations.size() > std::size_t(0u)) {
		tsg::print("Memory leakes: {}", m_allocations.size());
		/* computing losted bytes */
		std::size_t lost_bytes{};
		auto current = m_allocations.begin();
		while (current != m_allocations.end()) {
			lost_bytes += current->data.size();
			current = current->next;
		}
		tsg::print("Bytes losted: {}", lost_bytes);
	}
	else {
		tsg::print("No memory leaked");
	}
};
#include "detektor.h"
#include <tsg/io.h> // tsg::print

detektor::detektor() {
	tsg::print("Leak Detektor is awake and ready");
};
detektor::~detektor() {
	if (std::size_t size = m_allocations.size() > std::size_t(0u)) {
		tsg::print("Detektor found {} leakes", m_allocations.size());
		tsg::print("Bytes\t|\tFile\t|\tLine\t|\tFunction");
		std::size_t lost_bytes{};
		auto current = m_allocations.begin();
		while (current != m_allocations.end()) {
			lost_bytes += current->data.size();
			current = current->next;
			tsg::print("{} | {} | {} | {}", current->data.size(), current->data.get_file(), current->data.get_line(), current->data.get_function());
		}
		tsg::print("Bytes losted: {}", lost_bytes);
	}
	else {
		tsg::print("No memory leaked");
	}
	tsg::print("Detektor goes to sleep");
};
#include "container_leak.h"
#include <vector>
#include <map>

void container_leak::vector_test() {
	std::vector<int*> vec;
	for (std::size_t i = 0; i < 5; ++i) {
		vec.emplace_back(new int(10));
	}
}

void container_leak::map_test() {
	std::map<int, int*> map;
	map[1] = new int(20);
}
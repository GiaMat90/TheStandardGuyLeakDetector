//#include "tsld.h"
//#include "detektor.h"
//#include <new>
//
//static detektor g_detektor;
//
//
//struct where {
//	const char* file;
//	int line;
//	where(const char* f, int l) : file(f), line(l) {};
//};
//
//void* operator new(std::size_t n, const where& w) {
//	if(void* p = std::malloc(n)) {
//		g_detektor.add_allocation(n, p);
//		return p;
//	}
//	else {
//		throw std::bad_alloc();
//	}
//}
//
//void* operator new[](std::size_t n, const where& w) {
//	if(void* p = std::malloc(n)) {
//		g_detektor.add_allocation(n, p);
//		return p;
//	}
//	else {
//		throw std::bad_alloc();
//	}
//}
//
//void operator delete (void* p, std::size_t n) noexcept {
//	g_detektor.add_deallocation(p);
//	std::free(p);
//}
//
//void operator delete[](void* p, std::size_t n) noexcept {
//	g_detektor.add_deallocation(p);
//	std::free(p);
//}
//
//
//#define new new(where(__FILE__, __LINE__))

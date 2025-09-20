#pragma once

#include "detektor.h"
#include <new>

static detektor g_detektor;

/* placement new with file, function and line info */
void* operator new(std::size_t n, const where& w) {
	if (void* p = std::malloc(n)) {
		g_detektor.add_allocation(w.file, w.function, w.line, n, p);
		return p;
	}
	else {
		throw std::bad_alloc();
	}
}
void* operator new[](std::size_t n, const where& w) {
	if (void* p = std::malloc(n)) {
		g_detektor.add_allocation(w.file, w.function, w.line, n, p);
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
void operator delete (void* p, std::size_t n, where w) noexcept {
	if (p) {
		g_detektor.add_deallocation(p);
		std::free(p);
	}
}
void operator delete[](void* p, std::size_t n, where w) noexcept {
	if (p) {
		g_detektor.add_deallocation(p);
		std::free(p);
	}
}
/* Regular delete */
void operator delete (void* p, std::size_t n) noexcept {
	if (p) {
		g_detektor.add_deallocation(p);
		std::free(p);
	}
}
void operator delete[](void* p, std::size_t n) noexcept {
	if (p) {
		g_detektor.add_deallocation(p);
		std::free(p);
	}
}
/* macro substituition of operator new with a placement new with debugging info */
#define new new(where(__FILE__, __func__, __LINE__))




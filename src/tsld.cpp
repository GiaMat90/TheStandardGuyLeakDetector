#include "tsld.h"
#include <tsg/io.h>
#include <new>
#include <cassert>
#include <algorithm>

class allocation {
	using pointer_t = void*;
	using file_t = const char*;
	using line_t = int;
public:
	allocation() : m_file(), m_line(), m_ptr{ nullptr }, m_size() {};
	allocation(pointer_t p) : m_file(), m_line(), m_ptr(p), m_size() {};
	allocation(std::size_t s, pointer_t p) : m_file(), m_line(), m_ptr(p), m_size(s) {};
	allocation(file_t f, line_t l, std::size_t s, pointer_t p) : m_file(f), m_line(l), m_ptr(p), m_size(s) {};
	allocation(file_t f, line_t l) : m_file(f), m_line(l), m_ptr{ nullptr }, m_size() {};
	allocation(std::size_t s) : m_file(), m_line(), m_ptr{ nullptr }, m_size(s) {}
public:
	std::size_t size() const noexcept { return m_size; };
public:
	bool operator==(const allocation& other) const noexcept {
		return (m_ptr == other.m_ptr);
	}
private:
	pointer_t m_ptr{ nullptr };
	file_t m_file{};
	line_t m_line{};
	std::size_t m_size{};
public:
	static void* operator new(std::size_t n) {
		tsg::print("detektor::new called, size = {}", n);
		if (void* p = std::malloc(n)) {
			return p;
		}
		else {
			throw std::bad_alloc();
		}
	};
};

template<typename T>
class linked_list {
private:
	struct node_t {
		T data{};
		node_t* next{ nullptr };
		node_t* previous{ nullptr };
		node_t(const T& data, node_t* n, node_t* p) : data(data), next(n), previous(p) {};
	};
	node_t* m_begin{ nullptr };
	node_t* m_end{ nullptr };
	std::size_t m_size{ 0u };
public:
	std::size_t size() const { return m_size; }
	node_t* begin() const { return m_begin; }
	node_t* end() const { return m_end; }
public:
	template<typename...Args>
	bool push(Args... args) noexcept {
		if (void* ptr = std::malloc(sizeof(node_t))) {
			node_t* new_node = new (ptr) node_t{ T(args...), nullptr, nullptr }; // placement new
			if (m_begin) {
				new_node->previous = m_end;
				m_end->next = new_node;
				m_end = new_node;
			}
			else {
				m_begin = new_node;
				m_end = new_node;
			}
			++m_size;
			return true;
		}
		else {
			return false;
		}
	}

	node_t* find(const T& value) noexcept {
		node_t* current = m_begin;
		while (current) {
			if (current->data == value) {
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

	bool remove(const T& value) noexcept {
		if (node_t* node = find(value)) {
			if (node == m_begin) {
				if (m_size > 1u) {
					m_begin = m_begin->next;
					m_begin->previous = nullptr;
				}
				else {
					m_begin->next = nullptr;
					m_begin = nullptr;
				}
			}
			else if (node == m_end) {
				m_end = m_end->previous;
				m_end->next = nullptr;
			}
			else {
				node->previous->next = node->next;
				node->next->previous = node->previous;
			}
			std::free(node);
			node = nullptr;
			--m_size;
			return true;
		}
		else {
			return false;
		}
	}
};

class detektor {
public:
	detektor() {
		tsg::print("detektor::constructor called");
	};
	~detektor() {
		tsg::print("tsld report:");
		if (std::size_t size = m_allocations.size() > std::size_t(0u)) {
			tsg::print("Memory leakes: {}", m_allocations.size());
			/* computing losted bytes */
			std::size_t lost_bytes{};
			auto current = m_allocations.begin();
			while(current != m_allocations.end()){
				lost_bytes += current->data.size();
				current = current->next;
			}
			tsg::print("Bytes losted: {}", lost_bytes);
		}
		else {
			tsg::print("No memory leaked");
		}
	};
	template <typename...Args>
	void add_allocation(Args... args) {
		m_allocations.push(args...);
	};
	void add_deallocation(void* p) {
		m_allocations.remove(p);
	};
private:
	linked_list<allocation> m_allocations;
};

static detektor g_detektor;

void* operator new(std::size_t n) {
	if(void* p = std::malloc(n)) {
		g_detektor.add_allocation(n, p);
		return p;
	}
	else {
		throw std::bad_alloc();
	}
}

void* operator new[](std::size_t n) {
	if(void* p = std::malloc(n)) {
		g_detektor.add_allocation(n, p);
		return p;
	}
	else {
		throw std::bad_alloc();
	}
}

void operator delete (void* p, std::size_t n) noexcept {
	g_detektor.add_deallocation(p);
	std::free(p);
}

void operator delete[](void* p, std::size_t n) noexcept {
	g_detektor.add_deallocation(p);
	std::free(p);
}




#pragma once

#include <cstdlib> // std::malloc, std::free

template<typename T>
class linked_list {
	struct node_t {
		T data{};
		node_t* next{ nullptr };
		node_t* previous{ nullptr };
		node_t(const T& data, node_t* n, node_t* p) : data(data), next(n), previous(p) {};
	};
public:
	linked_list() = default;
	~linked_list() {
		node_t* current = m_begin;
		while (current) {
			node_t* next = current->next;
			std::free(current);
			current = next;
		}
		m_begin = nullptr;
		m_end = nullptr;
		m_size = 0u;
	};
public:
	inline std::size_t size() const { return m_size; }
	inline node_t* begin() const { return m_begin; }
	inline node_t* end() const { return m_end; }
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

	node_t* find(const T& value) const noexcept {
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
private:
	node_t* m_begin{ nullptr };
	node_t* m_end{ nullptr };
	std::size_t m_size{ 0u };
};
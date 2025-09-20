#include "allocation.h"
 
allocation::allocation() : 
	m_file(), m_function(), m_line(), m_ptr{ nullptr }, m_size() {};
allocation::allocation(pointer_t p) : 
	m_file(), m_function(), m_line(), m_ptr(p), m_size() {};
allocation::allocation(std::size_t s, pointer_t p) : 
	m_file(), m_function(), m_line(), m_ptr(p), m_size(s) {};
allocation::allocation(file_t f, function_t fun, line_t l, std::size_t s, pointer_t p) :
	m_file(f), m_function(fun), m_line(l), m_ptr(p), m_size(s) {};
allocation::allocation(file_t f, function_t fun, line_t l) :
	m_file(f), m_function(fun), m_line(l), m_ptr{ nullptr }, m_size() {};
allocation::allocation(std::size_t s) :
	m_file(), m_function(), m_line(), m_ptr{ nullptr }, m_size(s) {};
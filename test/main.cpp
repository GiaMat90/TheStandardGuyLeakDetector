#include <tsg/io.h>
#include <tsld.h>
#include <array>

template<typename T, std::size_t S, typename ...Args>
void no_leaks(Args... args) {
	std::array<T*, S> array;
	for (std::size_t i{}; i < S; ++i) {
		array[i] = new T(args...);
	}
	for (std::size_t i{}; i < S; ++i) {
		delete array[i];
	}
}
template<typename T, std::size_t S, typename ...Args >
void leaks(Args... args) {
	std::array<T*, 2*S> array;
	for (std::size_t i{}; i < 2 * S; ++i) {
		array[i] = new T(args...);
	}
	for (std::size_t i{}; i < 2 * S; ++i) {
		if (i % 2 > 0) { 
			delete array[i]; 
		}
	}
}
int main() {
	tsg::print("Hello, World!\n");
	
	no_leaks<int, 100>(42);
	leaks<int, 100>(42);

	return 0;
}
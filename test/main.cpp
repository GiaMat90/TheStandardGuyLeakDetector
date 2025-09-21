/*
 * Copyright 2025 Giacomo Matzeu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <array>

// use detekt to catch memory leaks
#include <detekt.h>

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
	// no leaks of int
	no_leaks<int, 100>(42);
	// 100 leaks of int
	leaks<int, 100>(42);
	// one leak
	int* p = new int(42);
	*p; // avoid unused variable warning

	return 0;
}

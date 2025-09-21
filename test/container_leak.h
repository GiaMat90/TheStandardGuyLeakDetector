#pragma once

class container_leak {
public:
	container_leak() = default;
	~container_leak() = default;
public:
	static void vector_test();
	static void map_test();
};
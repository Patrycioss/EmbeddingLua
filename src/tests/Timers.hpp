#pragma once
#include <chrono>

class NanoTimer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
	void Start()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	[[nodiscard]] std::chrono::nanoseconds Stop() const
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	}
};

class MicroTimer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
	void Start()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	[[nodiscard]] std::chrono::microseconds Stop() const
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
	}
};

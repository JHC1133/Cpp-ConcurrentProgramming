#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>



template<typename T>
void print(T type) {

	std::cout << type << "\n";
}

void print_vector(std::vector<int>& vec) {

	print("Printing Vector: ");

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		std::cout << *it << " ";
	}

	print(" ");
}

// 1.1
void thread_increment(std::vector<int>& vec) {

	print("thread working in thread_increment");

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		*it += 1;
	}
}

// 1.2
void increment_range(std::vector<int>& vec, int start, int end, int increment) {

	std::cout << "Incrementing from start " << start << " to end " << end << " with increment: " << increment << "\n";
	for (size_t i = start; i < end; ++i)
	{
		vec[i] += increment;
	}
}

void thread_N_increment(std::vector<int>& vec, int N) {

	std::vector<std::thread> threads;

	int threadRange = vec.size() / N;

	print(threadRange);

	for (size_t i = 0; i < N; ++i)
	{
		int start = i * threadRange;
		int end = start + threadRange;

		// Constructs thread while placing in vector
		threads.emplace_back(increment_range, std::ref(vec), start, end, i);

		//threads[i] = std::thread(increment_range, std::ref(vec), start, end, i); // Error: copy not allowed

		//std::cout << "Thread " << threads[i].get_id() << " is working" << "\n";
	}

	for (auto& t : threads) {

		std::cout << "Thread " << t.get_id() << " is joining" << "\n";

		t.join();
	}

	print_vector(vec);
}
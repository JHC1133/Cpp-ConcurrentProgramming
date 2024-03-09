#pragma once
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

// 2.1, 2.2, 2.3

static size_t ID = 0;

std::mutex mtx;

class SpecialThread {

public:

	std::thread t;
	size_t id;

	SpecialThread() {
		id = ID++;
	}

	void start(int x) {

		// From Lecture 8:
		// threads[i] = std::thread(access_shared_resource, i); This style gives me copy-construct errors, since thread does not allow copy

		// 2.1
		if (x == 1)
		{
			t = std::thread([this] {this->thread_execute(); });
		}

		//2.2
		if (x == 2)
		{
			t = std::thread([this] {this->thread_execute_mutex(); });
		}

		// 2.3
		if (x == 3)
		{
			t = std::thread([this] {this->thread_execute_lock_guard(); });
		}
	}


private:

	// 2.1
	void thread_execute() {

		std::cout << "Hello" << " from " << " thread " << id << "!" << "\n";
	}

	// Prints the output in a chaotic manner, my guess is that it's based upon race condition

	// 2.2
	void thread_execute_mutex() {

		mtx.lock();

		std::cout << "Hello" << " from " << " thread " << id << "!" << "\n";

		mtx.unlock();
	}

	// Prints the output correctly, however in non-deterministic order of thread execution

	// 2.3
	void thread_execute_lock_guard() {

		std::lock_guard<std::mutex> lock(mtx);
		std::cout << "Hello" << " from " << " thread " << id << "!" << "\n";
	}

	// Prints the output correctly AND in the same order as the threads are indexed in the vector
};
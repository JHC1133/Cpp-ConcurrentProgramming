// Labb4ConcurrentProgramming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

#include "ThreadIncrement.h"
#include "ThreadSafety.h"
#include "ConcurrentTextFileSearch.h"
#include "ConcurrentProdCon.h"

int main()
{
#pragma region 1.1 - 1.2

	// 1.1

   /* std::vector<int> myVector(20, 0);

	print_vector(myVector);

	std::thread t(thread_increment, std::ref(myVector));

	t.join();

	print_vector(myVector);*/

	// 1.2

	/*std::vector<int> myVector(20, 0);

	thread_N_increment(std::ref(myVector), 4);*/

#pragma endregion

	
#pragma region 2.1 - 2.3

	// 2.1, 2.2, 2.3

	//std::vector<SpecialThread> sThreads(10);

	//for (size_t i = 0; i < sThreads.size(); i++)
	//{
	//	//sThreads[i].start(1);
	//	//sThreads[i].start(2);
	//	sThreads[i].start(3);
	//}

	//for (size_t i = 0; i < sThreads.size(); i++)
	//{
	//	sThreads[i].t.join();
	//}

#pragma endregion
	

#pragma region 3.1
	// 3.1

	/*TextFileHandler myConverter;

	std::string text_file = "bible.txt";
	std::ifstream myFile(text_file);
	std::string word = "God";
	int N = 10;

	if (!myFile.is_open())
	{
		std::cout << "Error opening provided file" << "\n";
	}

	std::cout << "Number of available hardware threads: " << std::thread::hardware_concurrency() << "\n";
	std::cout << "Number of threads used for searching, N = " << N << "\n";
	std::cout << "Searching " << text_file << " for word " << word << "\n";

	myConverter.convert_file(std::move(myFile));
	myConverter.search_file(word, N);

	std::cout << "Total matches found: " << global_word_counter << "\n";
	std::cout << "Total execution time: " << global_timer_sum << "\n";*/

#pragma endregion


#pragma region 4

	buffer.reserve(max_number_orders);

	std::thread producers[] = {
		std::thread(produce_order, thread_counter++),
		std::thread(produce_order, thread_counter++),
		std::thread(produce_order, thread_counter++),
		std::thread(produce_order, thread_counter++),
		std::thread(produce_order, thread_counter++)
	};

	std::this_thread::sleep_for(std::chrono::milliseconds(150));

	std::thread consumers[] = {
		std::thread(consume_order, 1),
		std::thread(consume_order, 2)
	};

	for (auto& t : producers) {
		t.join();
	}

	for (auto& t : consumers) {
		t.join();
	}

#pragma endregion

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

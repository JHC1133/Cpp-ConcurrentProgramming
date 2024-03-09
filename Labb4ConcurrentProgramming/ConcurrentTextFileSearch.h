#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <mutex>
#include <string>

void ifstream_open_check(const std::ifstream& file) {

    if (!file.is_open())
    {
        std::cout << "Error opening provided file" << "\n";
    }
}

static int global_word_counter = 0;
static auto global_timer_sum = 0;

class TextFileHandler {

private:

    std::vector<std::thread> m_threads;
    std::vector<std::string> m_strings;
    std::ifstream m_file;
    std::mutex mtx;

    void search_range(int start, int end, const std::string word) {

        std::lock_guard<std::mutex> lock(mtx);
        int counter = 0;

        auto startTimer = std::chrono::high_resolution_clock::now();

        for (size_t i = start; i < end; ++i)
        {
            if (m_strings[i] == word)
            {
                counter++;
            }
        }

        auto endTimer = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startTimer);
        auto execution_time_ms = duration.count();

        std::cout << "Thread ID: " << std::this_thread::get_id() << " found " << counter << " occurrences of " << word << " in " << execution_time_ms << " ms " << "\n";

        global_word_counter += counter;
        global_timer_sum += execution_time_ms;
    }

public:

    TextFileHandler()
    {

    }

    void convert_file(std::ifstream&& file) {

        m_file = std::move(file);

        if (!m_file.is_open())
        {
            std::cout << "Error opening provided file" << "\n";
        }

        std::string line;

        while (std::getline(m_file, line))
        {
            std::istringstream linestream(line);
            std::string word;

            while (linestream >> word) // extracts words based on whitespace
            {
                m_strings.push_back(word);
            }
        }
    }

    // N number of threads searching concurrently for word
    void search_file(const std::string word, int N) {

        std::vector<std::thread> threads;
        int threadRange = m_strings.size() / N;

        std::cout << "Lines per thread " << threadRange << "\n";

        for (size_t i = 0; i < N; i++)
        {
            int start = i * threadRange;
            int end = start + threadRange;

            threads.emplace_back(&TextFileHandler::search_range, this, start, end, word);
        }

        for (auto& t : threads) {
            t.join();
        }
    }

};

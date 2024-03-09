#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <cstdlib>
#include <condition_variable>


static int global_order_id;

struct Order {
    int customer_id;
    int order_id;
};

std::vector<Order> buffer;

const int max_number_producers = 5;
const int max_number_consumers = 2;
const int max_number_orders = 5;

thread_local int thread_counter = 0;
int order_counter = 0;

std::mutex order_mutex;
std::condition_variable order_cv;

void produce_order(int customerId) {

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    {
        std::unique_lock<std::mutex> lock(order_mutex);
        order_cv.wait(lock, [&]() {return buffer.size() < max_number_orders; }); // waits until buffer contains an order

        buffer.push_back({ customerId, order_counter++ });

        std::cout << "Customer " << customerId << " placed order: " << order_counter << "\n";
    }
}

void consume_order(int baristaId) {

    while (true) { // Keep processing until no more orders
        Order order;
        {
            std::unique_lock<std::mutex> lock(order_mutex);
            if (order_cv.wait_for(lock, std::chrono::seconds(1), [&] { return !buffer.empty(); })) {
                order = buffer.back();
                buffer.pop_back();
            }
            else {
                break; // No orders to process within the timeout
            }
        }

        std::cout << "Barista " << baristaId << " started order " << order.order_id << "\n";

        int max_range = 3;

        for (size_t i = 0; i <= 100; i += 20)
        {
            int processTime = rand() % max_range + 1; // gives psuedo-random number from 1 to range
            std::this_thread::sleep_for(std::chrono::seconds(processTime));

            std::cout << "Barista " << baristaId << ": Order " << order.order_id << " progress: " << i << " %" << "\n";
        }

        std::cout << "Barista " << baristaId << " completed order " << order.order_id << "\n";
        order_cv.notify_one();
    }
}
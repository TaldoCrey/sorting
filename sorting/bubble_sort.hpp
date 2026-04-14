#pragma once
#include "../structures/vec.hpp"
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

void bubble_sort(Vec* v, mutex& mtx) {
    while (!sorted(v)) {
        for (int j = 0; j < v->getSize() - 1; j++) {
            if ((*v)[j + 1] < (*v)[j]) {
                {
                    lock_guard<mutex> lock(mtx);
                    troca(v, j + 1, j);
                }
                this_thread::sleep_for(chrono::milliseconds(25));
            }
        }
    }
}
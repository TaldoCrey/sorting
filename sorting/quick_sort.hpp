#pragma once
#include "../structures/vec.hpp"
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

int sep(Vec *v, int start, int end, mutex& mtx) {
    int i, j;
    int c = (*v)[end];
    i = start;
    for (j = start; j < end; j++) {
        if ((*v)[j] <= c) {
            {
                lock_guard<mutex> lock(mtx);
                troca(v, i, j);
            }
            this_thread::sleep_for(chrono::milliseconds(25));
            i++;
        }
    }
    troca(v, i, end);
    return i;
}

void qsort(Vec* v, int start, int end, mutex& mtx) {
    int off, sep_i;
    if (end > start) {
        off = randInt(0, end - start);
        troca(v, start+off, end);
        sep_i = sep(v, start, end, mtx);
        qsort(v, start, sep_i - 1, mtx);
        qsort(v, sep_i + 1, end, mtx);
    }  
}

void quick_sort(Vec *v, mutex& mtx) {
    if (v->getSize() <= 1) {
        return;
    }

    qsort(v, 0, v->getSize() - 1, mtx);
}
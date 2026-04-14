#pragma once
#include "../structures/vec.hpp"
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

void merge(Vec* v, int start, int sep, int end, mutex& mtx) {
    int i, j, k, tam;
    i = start;
    j = sep;
    k = 0;
    tam = end - start;
    Vec aux = Vec(tam);
    while (i < sep && j < end) {
        if ((*v)[i] <= (*v)[j]) aux[k++] = (*v)[i++];
        else aux[k++] = (*v)[j++];
    }

    while (i < sep) aux[k++] = (*v)[i++];
    while (j < end) aux[k++] = (*v)[j++];
        for (k = 0; k < tam; k++) {
            {
                lock_guard<mutex> lock(mtx);
                (*v)[start + k] = aux[k];
            }
            this_thread::sleep_for(chrono::milliseconds(25));
        }
    
    //testar
}

void msort(Vec* v, int start, int end, mutex& mtx) {
    int m;
    if (end - start > 1) {
        m = (start + end) / 2;
        msort(v, start, m, mtx);
        msort(v, m, end, mtx);
        merge(v, start, m, end, mtx);
    }
}

void merge_sort(Vec* v, mutex& mtx) {
    if (v->getSize() <= 1) {
        return;
    }

    msort(v, 0, v->getSize(), mtx);
}
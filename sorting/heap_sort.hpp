#include "../structures/heap.hpp"
#include <mutex>
#include <chrono>
#include <thread>

void heap_sort(Heap *h, mutex &mtx) {
    int i, m;
    for (i = 1; i < h->getVec()->getSize(); i++) {
        {
            lock_guard<mutex> lock(mtx);
            h->sobeHeap(i);
            
        }
        this_thread::sleep_for(chrono::milliseconds(15));
    }

    for (m = h->getVec()->getSize(); m > 0; m--) {
        {
            lock_guard<mutex> lock(mtx);
            troca(h->getVec(), 0, m - 1);
            h->desceHeap(0, m - 1);
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
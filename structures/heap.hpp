#pragma once
#include "vec.hpp"
#include "../utils/random.hpp"
#include <iostream>

#define PAI(i) ((i - 1) / 2)
#define FILHO_ESQ(i) ((2 * i) + 1)
#define FILHO_DIR(i) ((2 * i) + 2)

class Heap {
    private:
        Vec *v;
    public:
        Heap();
        Heap(Vec* v);

        void sobeHeap(int pos);
        void desceHeap(int pos, int m);

        void insereHeap(int x);
        int removeHeap();

        Vec* getVec();

        //~Heap();
};

Heap::Heap() {
    Vec temp = Vec();
    this->v = &temp;
}

Heap::Heap(Vec* v) {
    this->v = v;
}

void Heap::sobeHeap(int pos) {
    int current = pos;
    while (current > 0 && (*this->v)[PAI(current)] < (*this->v)[current]) {
        troca(this->v, current, PAI(current));
        current = PAI(current);
    }
}

void Heap::insereHeap(int x) {
    this->v->push(x);
    sobeHeap(this->v->getSize() - 1);
}

void Heap::desceHeap(int pos, int m) {
    int current = pos, filho;
    while (FILHO_ESQ(current) < m && ((*this->v)[FILHO_ESQ(current)] > (*this->v)[current]
     || (FILHO_DIR(current) < m && (*this->v)[FILHO_DIR(current)] > (*this->v)[current]))) {
        filho = FILHO_ESQ(current);
        if (FILHO_DIR(current) < m && (*this->v)[FILHO_DIR(current)] > (*this->v)[filho])
            filho = FILHO_DIR(current);

        troca(this->v, current, filho);
        current = filho;
    }
}

int Heap::removeHeap() {
    int ret = (*this->v)[0];
    troca(this->v, 0, this->v->getSize() - 1);
    desceHeap(0, this->v->getSize());
    this->v->pop();
    return ret;
}

void preenche(Heap *h, int n, int min = 0, int max = 100) {
    for (int i = 0; i < n; i++) {
        h->insereHeap(randInt(min, max));
    }
}

Vec* Heap::getVec() {
    return this->v;
}
#pragma once
#include <stdlib.h>

using namespace std;

struct Node {
    int value;
    int index;
    Node* next;
    Node* prev;
} typedef Node;

class Vec {
    private:
        int size;
        Node* start;
        Node* end;

        Node* fixIndex(Node* current);
    public:
        Vec();

        int getSize();
        Node* getStart();
        Node* getEnd();
        void push(int x);
        int pop();
        int pop(int i);
        int& operator[](size_t index);

        ~Vec();

};

void mostra(Vec *v);

void preenche(Vec *v, int n);
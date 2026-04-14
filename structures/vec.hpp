#pragma once
#include <stdlib.h>
#include "../utils/random.hpp"
#include <iostream>

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
        Vec(int n);

        int getSize();
        Node* getStart();
        Node* getEnd();
        void push(int x);
        int pop();
        int pop(int i);
        int& operator[](size_t index);
        void clear();

        ~Vec();
};

Vec::Vec() {
    this->start = nullptr;
    this->end = nullptr;
    this->size = 0;
}

Vec::Vec(int n) {
    this->start = nullptr;
    this->end = nullptr;
    this->size = 0;

    for (int i = 0; i < n; i++) {
        this->push(0);
    }
}

Node* Vec::fixIndex(Node* current) {
    Node* deletedNode = current;
    int swap = current->index;
    int i;
    while (current->next != nullptr) {
        current = current->next;
        i = current->index;
        current->index = swap;
        swap = i;
    }

    return deletedNode;
}

int Vec::getSize() {
    return this->size;
}

Node* Vec::getStart() {
    return this->start;
}

Node* Vec::getEnd() {
    return this->end;
}

void Vec::push(int x) {
    Node* aux = new Node;
    aux->index = this->size;
    aux->value = x;
    aux->next = nullptr;
    aux->prev = this->end;

    if (this->size == 0) {
        this->start = aux;
    }

    if (this->size > 0) {
        this->end->next = aux;
    }
    
    this->end = aux;
    this->size++;
}

int Vec::pop() {
    if (this->size == 0) throw runtime_error("Vector is already empty");

    Node *aux = this->end;
    this->end = aux->prev;

    this->end->next = nullptr;
    
    int i = aux->value;

    delete aux;
    this->size--;
    return i;
}

int Vec::pop(int i) {
    if (this->size == 0) throw runtime_error("Vector is already empty");
    
    if (i < 0 || i > this->size - 1) throw runtime_error("Invalid index");

    if (i == this->size - 1) {
        return this->pop();
    }

    if (i == 0) {
        int ret = this->start->value;
        Node* del = fixIndex(this->start);
        this->start = del->next;
        del->next->prev = nullptr;
        delete del;
        size--;
        return ret;
    }
    
    Node* aux;
    if ((this->size - 1) - i < i) {
        aux = this->end;

        while (aux != nullptr && aux->index != i) aux = aux->prev;

        if (aux == nullptr) throw runtime_error("Something went wrong.");
    } else {
        aux = this->start;

        while (aux != nullptr && aux->index != i) aux = aux->next;

        if (aux == nullptr) throw runtime_error("Something went wrong.");
    }

    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;

    Node* del = fixIndex(aux);

    int ret = del->value;

    del->next->prev = del->prev;
    del->prev->next = del->next;

    delete del;
    size--;
    return ret;
}

int& Vec::operator[](size_t index) {
    if (index < 0 || index >= this->size) throw runtime_error("Invalid index");

    if (this->size == 0) throw runtime_error("Empty vector has no elements");

    Node* aux;
    if ((this->size - 1) - index < index) {
        
        aux = this->end;

        while (aux != nullptr && aux->index != index) aux = aux->prev;

        if (aux == nullptr) throw runtime_error("Something went wrong.");
    } else {
        aux = this->start;

        while (aux != nullptr && aux->index != index) aux = aux->next;

        if (aux == nullptr) throw runtime_error("Something went wrong.");
    }


    return aux->value;
}

void Vec::clear() {
    Node* current = this->start;

    while(current != nullptr) {
        this->start = current->next;
        delete current;
        current = this->start;
    }

    this->start = nullptr;
    this->end = nullptr;
    this->size = 0;
}

Vec::~Vec() {
    Node* current = this->start;

    while(current != nullptr) {
        this->start = current->next;
        delete current;
        current = this->start;
    }
}

void mostra(Vec *v) {
    cout << "[ ";
    for (int i = 0; i < v->getSize(); i++) {
        cout << (*v)[i] << " ";
    }
    cout << "]" << endl;
}

void preenche(Vec *v, int n, int min = 0, int max = 100) {
    for (int i = 0; i < n; i++) {
        v->push(randInt(min, max));
    }
}

void troca(Vec *v, int a, int b) {
    int swap = (*v)[a];
    (*v)[a] = (*v)[b];
    (*v)[b] = swap;
}

bool sorted(Vec *v) {
    for (int i = 0; i < v->getSize() - 2; i++) {
        if ((*v)[i] > (*v)[i+1]) {
            return false;
        }
    }
    return true;
}
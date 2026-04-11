#pragma once
#include "random.hpp"

int randInt(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> d(min, max);

    return d(gen);
}
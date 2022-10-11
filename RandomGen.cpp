//
// Created by TanaD on 4/10/2022.
//

#include "RandomGen.h"
#include <ctime>

std::mt19937 RandomGen::random(time(0));

int RandomGen::RandomNumber(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}
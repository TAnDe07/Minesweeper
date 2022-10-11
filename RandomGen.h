//
// Created by tanad on 4/10/2022.
//
#include <random>
#include <ctime>
#pragma once

class RandomGen {
    static std::mt19937 random;
public:
    static int RandomNumber(int min, int max);
};
//
// Created by tanad on 4/15/2022.
//

#pragma once
#include "Texture.h"
using namespace std;
#include <SFML/Graphics.hpp>

struct Mines {
    sf::Sprite mines1;
    float x;
    float y;
public:
    Mines(sf::Sprite text, float x1, float y1) {
        mines1 = text;
        x = x1;
        y = y1;
    }
};
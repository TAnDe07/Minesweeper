//
// Created by tanad on 4/15/2022.
//

#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

struct MiscelaneousButtons {
    sf::Sprite Misc;
    string name;
    float buttonXMin;
    float buttonYMin;
    float buttonXMax;
    float buttonYMax;

    MiscelaneousButtons(string name1, sf::Sprite text, float x, float y) {
        name = name1;
        Misc = text;
        buttonXMin = x;
        buttonYMin = y;
        buttonXMax = x + 64;
        buttonYMax = y + 64;
    }

};
//
// Created by tanad on 4/15/2022.
//
#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "RandomGen.h"
#pragma once
using namespace std;

struct Tile {
    sf::Sprite tile;
    char mineOrNot;
    float minimumX;
    float maximumX;
    float minimumY;
    float maximumY;
    int revealed;
    int flag;
    int mineCount; // number of adjacent mines
    vector<Tile*> adjacentTiles;
    int recursiveRevealed;

    Tile (sf::Sprite text, float x, float y, char random, int r, int f, vector<Tile*> adjacent, int mineCount1, int RR) {
        mineOrNot = random;
        tile = text;
        minimumX = x;
        minimumY = y;
        maximumY = y + 32;
        maximumX = x + 32;
        revealed = r;
        flag = f;
        adjacentTiles = adjacent;
        mineCount = mineCount1;
        recursiveRevealed = RR;
    }

};
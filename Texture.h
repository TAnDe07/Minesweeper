//
// Created by TanaD on 4/10/2022.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RandomGen.h"
#include <unordered_map>
using std::unordered_map;
using std::string;

class Texture {
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);
public:
    static sf::Texture& GetTexture(string textureName);
    static void clear();
};
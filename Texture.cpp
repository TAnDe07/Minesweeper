//
// Created by tanad on 4/10/2022.
//
#include "Texture.h"

unordered_map<string, sf::Texture> Texture::textures;

void Texture::LoadTexture(string textureName) {
    string path = "images/";
    path += textureName + ".png";

    textures[textureName].loadFromFile(path);
}

sf::Texture& Texture::GetTexture(string textureName) {
    if(textures.find(textureName) == textures.end()) {
        LoadTexture(textureName);
    }
    return textures[textureName];
}
void Texture::clear() {
    textures.clear();
}
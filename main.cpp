#include <SFML/Graphics.hpp>
#include <iostream>
#include "RandomGen.h"
#include "Texture.h"
#include "Mines.h"
#include "Tile.h"
#include "MiscelaneousButtons.h"
#include <fstream>
using namespace std;

//Draws current number of mines
void DrawDigit(int mimes, sf::Sprite digits, int rows, sf::RenderWindow &window) {
    int currentDigit = 0;
    vector<int> mimesDigit;
    int iterator = 1;
    float w = 0;

    //draws minus sign if negative
    if(mimes < 0) {
        digits.setTextureRect(sf::IntRect(21 * 10, 0, 21 , 32));
        digits.setPosition(w, rows * 32);
        window.draw(digits);
    }

    mimes = abs(mimes);
    int currentNum = mimes;

    //adds number of mines digit by digit in vector
    while (iterator == 1) {
        if (mimes < 10 && mimes >= 0) {
            currentDigit = mimes;
            iterator = 0;
        }
        else {
            if (currentNum < 10) {
                currentDigit = currentNum;
                iterator = 0;
            }
            else {
                currentDigit = currentNum % 10;
                currentNum /= 10;
            }
        }
        mimesDigit.push_back(currentDigit);
    }

    //adds leading 0s if applicable
    if (mimes < 100) {
        mimesDigit.push_back(0);
        if (mimes < 10) {
            mimesDigit.push_back(0);
        }
    }

    vector<sf::Sprite> digits1;
    //Draws number in the correct location
    for (int i = mimesDigit.size() - 1; i >= 0; i--) {
        w += 21;
        if (mimesDigit.at(i) == 0) {
            digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
        } else if (mimesDigit.at(i) == 1) {
            digits.setTextureRect(sf::IntRect(21, 0, 21, 32));
        } else if (mimesDigit.at(i) == 2) {
            digits.setTextureRect(sf::IntRect(21 * 2, 0, 21, 32));
        } else if (mimesDigit.at(i) == 3) {
            digits.setTextureRect(sf::IntRect(21 * 3, 0, 21, 32));
        } else if (mimesDigit.at(i) == 4) {
            digits.setTextureRect(sf::IntRect(21 * 4, 0, 21, 32));
        } else if (mimesDigit.at(i) == 5) {
            digits.setTextureRect(sf::IntRect(21 * 5, 0, 21, 32));
        } else if (mimesDigit.at(i) == 6) {
            digits.setTextureRect(sf::IntRect(21 * 6, 0, 21, 32));
        } else if (mimesDigit.at(i) == 7) {
            digits.setTextureRect(sf::IntRect(21 * 7, 0, 21, 32));
        } else if (mimesDigit.at(i) == 8) {
            digits.setTextureRect(sf::IntRect(21 * 8, 0, 21, 32));
        } else if (mimesDigit.at(i) == 9) {
            digits.setTextureRect(sf::IntRect(21 * 9, 0, 21 , 32));
        }
        digits1.push_back(digits);
        digits.setPosition(w, rows * 32);
        window.draw(digits);
    }
}

//loads test, if test button is pressed
void LoadTest(int number, vector<vector<Tile>> &hiddenTile,  int rows, int &tempMine, int &tempMine2) {

    string test = "testBoard";
    test += to_string(number) + ".brd";
    ifstream inFile(test);

    //loads test
    string characterFile;
    while (inFile.is_open() && !inFile.eof()) {
        for (int j = 0; j < rows; ++j) {
            getline(inFile, characterFile);
            for (int i = 0; i < characterFile.size(); ++i) {
                if(characterFile.at(i) == '1') {
                    tempMine++;
                }
                hiddenTile[j].at(i).mineOrNot = (characterFile.at(i));
                hiddenTile[j].at(i).flag = 0;
                hiddenTile[j].at(i).revealed = 0;

            }
        }
    }


    tempMine2 = tempMine;
    cout << "test" << number << hiddenTile[0].at(0).mineOrNot << endl;
    cout << "test" << number << hiddenTile[0].at(1).mineOrNot << endl;

}

//creates 2d vector of tiles
vector<vector<Tile>> CreateTile(int rows, int columns, sf::Sprite hiddenTile, int &mineCount) {
    float x =0;
    float y = 0;
    vector<vector<Tile>> tiles;
    int mineCountTemp = mineCount;
    mineCount = 0;
    int random1;
    int random2;

    for (int i = 0; i < rows; ++i) {
        vector<Tile> temp;
        x = 0;
        if (i != 0) {
            y += 32;
        }
        for (int j = 0; j < columns; ++j) {
            vector<Tile *> adjacentTiles;
            Tile tile1(hiddenTile, x, y, 48, 0, 0, adjacentTiles, 0, 0);
            temp.push_back(tile1);
            x += 32;
        }
        tiles.push_back(temp);
    }

    for (int i = 0; i < mineCountTemp; ++i) {
        random1 = RandomGen::RandomNumber(0, rows - 1);
        random2 = RandomGen::RandomNumber(0, columns - 1);
        if (tiles[random1].at(random2).mineOrNot == '0') {
            tiles[random1].at(random2).mineOrNot = '1';
        }
        else {
            i--;
        }
    }
    mineCount = mineCountTemp;
    return tiles;
}

//creates vector for adjacent tiles and assigns to corresponding tile
void CreateAdjacentTile(vector<vector<Tile>> &hiddenTile,  int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            //first row
            if (i == 0) {
                //first tile in first rows
                if (j == 0) {
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j + 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j + 1));
                }
                //last tile in first rows
                else if (j == columns - 1){
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j - 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j - 1));
                }
                //other tiles in first row
                else {
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j - 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j + 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j - 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j + 1));
                }

            }
            //last row
            else if (i == rows - 1) {
                //first tile in last rows
                if (j == 0) {
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j + 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j + 1));
                }
                //last tile in last rows
                else if (j == columns - 1){
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j - 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j - 1));
                }
                //other tiles in last row
                else {
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j - 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j + 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j - 1));
                    hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j + 1));
                }
            }
            //first tiles in rows that are between first and last row
            else if (j == 0 && i != 0 && i != rows - 1 ) {
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j + 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j + 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j + 1));
            }
            //last tiles in rows that are between first and last row
            else if (j == columns - 1 && i != 0 && i != rows - 1) {
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j - 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j - 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j - 1));
            }
            //every other tiles in rows between first and last row
            else {
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j - 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i].at(j + 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j - 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i - 1].at(j + 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j - 1));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j));
                hiddenTile[i].at(j).adjacentTiles.push_back(&hiddenTile[i + 1].at(j + 1));

            }
        }
    }
}

//reveal tiles recursively
void RevealTileRecursive(Tile &tiles, int rows, int columns, sf::Sprite hiddenTile, vector<sf::Sprite> numbers){
    int noMine= 0;
    int mineCount = 0;
    for (int i = 0; i < tiles.adjacentTiles.size(); ++i) {
        if(tiles.adjacentTiles.at(i)->mineOrNot == '0') {
            noMine++;
        }
    }
    //base case
    if (noMine != tiles.adjacentTiles.size()) {
        for (int i = 0; i < tiles.adjacentTiles.size(); ++i) {
            if (tiles.adjacentTiles.at(i)->mineOrNot == '1') {
                mineCount++;
            }
        }
        tiles.revealed = 1;
        tiles.recursiveRevealed = 1;
        if (tiles.flag == 0) {
            tiles.tile.setTexture(Texture::GetTexture("tile_revealed"));
        }
        tiles.mineCount = mineCount;
        return;
    }
    else if (tiles.recursiveRevealed == 1) {
        tiles.revealed = 1; ////
        return;
    }
    ///helppsspspsppslpsldo
    else if (tiles.recursiveRevealed != 1) {
        for (int i = 0; i < tiles.adjacentTiles.size(); ++i) {
                tiles.adjacentTiles.at(i)->revealed = 1;
                tiles.recursiveRevealed = 1;
                tiles.adjacentTiles.at(i)->tile.setTexture(Texture::GetTexture("tile_revealed"));
            if (tiles.adjacentTiles.at(i) != nullptr) {
                RevealTileRecursive(*tiles.adjacentTiles.at(i), rows, columns, hiddenTile, numbers);
            }
        }
        return;
    }
}

int main() {
    /*************************** Read File Data **********************************/
    //read values from config.cfg file
    ifstream inFile("config.cfg");

    string columns;
    string rows;
    string mimes1;

    getline(inFile, columns);
    getline(inFile, rows);
    getline(inFile, mimes1);

    //window size
    int width = stoi(columns) * 32;
    int height = (stoi(rows) * 32) + 100;
    int mineCount = stoi(mimes1);
    int tileCount = (stoi(columns)) * (stoi(rows));
    int tempMineCount = mineCount;
    int tempMineCount2 = mineCount;

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);

    /************************************ Textures ******************************************/
    sf::Sprite hiddenTile;
    hiddenTile.setTexture(Texture::GetTexture("tile_hidden"));
    sf::Sprite revealedTile;
    revealedTile.setTexture(Texture::GetTexture("tile_revealed"));
    sf::Sprite mineTexture;
    mineTexture.setTexture(Texture::GetTexture("mine"));

    vector<sf::Sprite> numbers;
    for (int i = 0; i < 8; ++i) {
        numbers.push_back(revealedTile);
        string number = "number_";
        number += (to_string(i + 1));
        numbers.at(i).setTexture(Texture::GetTexture(number));
    }

    int yNumber = stoi(rows) * 32;
    float halfWidth = width / 2;
    sf::Sprite mrSmiley;
    mrSmiley.setTexture(Texture::GetTexture("face_happy"));
    mrSmiley.setOrigin(32, 0);
    mrSmiley.setPosition((halfWidth), yNumber);
    sf::Sprite winSmiley;
    winSmiley.setTexture(Texture::GetTexture("face_win"));
    winSmiley.setOrigin(32, 0);
    winSmiley.setPosition((halfWidth), yNumber);
    sf::Sprite loseSmiley;
    loseSmiley.setTexture(Texture::GetTexture("face_lose"));
    loseSmiley.setOrigin(32, 0);
    loseSmiley.setPosition((halfWidth), yNumber);

    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
    test1.setTexture(Texture::GetTexture("test_1"));
    test2.setTexture(Texture::GetTexture("test_2"));
    test3.setTexture(Texture::GetTexture("test_3"));

    sf::Sprite debug;
    debug.setTexture(Texture::GetTexture("debug"));
    sf::Sprite flag;
    flag.setTexture(Texture::GetTexture("flag"));
    sf::Sprite digits;
    digits.setTexture(Texture::GetTexture("digits"));


    float maxYHidden;
    float maxXHidden;

    //creates the tiles
    vector<vector<Tile>> tiles = CreateTile(stoi(rows), stoi(columns), hiddenTile, mineCount);
    CreateAdjacentTile(tiles, stoi(rows), stoi(columns));
    maxYHidden = 32 * stoi(rows);
    maxXHidden = stoi(columns) * 32;

    vector<Tile*> adjacentTiles;

    vector<MiscelaneousButtons> otherButtons;
    string name;

    //creates randoms buttons
    name = "mrSmiley";
    otherButtons.push_back(MiscelaneousButtons(name, mrSmiley, (halfWidth - 32), yNumber));
    name = "debug";
    otherButtons.push_back(MiscelaneousButtons(name, debug, halfWidth + (3 * 32), yNumber));
    name = "test1";
    otherButtons.push_back(MiscelaneousButtons(name, test1, halfWidth + (5 * 32), yNumber));
    name = "test2";
    otherButtons.push_back(MiscelaneousButtons(name, test2, halfWidth + (7 * 32), yNumber));
    name = "test3";
    otherButtons.push_back(MiscelaneousButtons(name, test3, halfWidth + (9 * 32), yNumber));

    int endGame = 0;
    bool loseOrWin = true;
    bool debug1 = false;
    int done = 0;
    int clickedMine = 0;

    /****************************** Window is open ***********************************/
    while (window.isOpen()) {
            /*************************** Board Setup **********************************/

            window.clear(sf::Color(255, 255, 255));

        //draws tiles
        for (int j = 0; j < stoi(rows) ; ++j) {
            for (int i = 0; i < stoi(columns); ++i) {

                //win???
                int streaks = tileCount - tempMineCount2;
                for (int k = 0; k < stoi(rows); ++k) {
                    for (int l = 0; l < stoi(columns); ++l) {
                        if ((tiles[k].at(l).revealed == 1) && (tiles[k].at(l).mineOrNot == '0') && (tiles[k].at(l).flag == 0)) {
                            streaks--;
                        }
                    }
                }


                //debug
                if (debug1 == true && streaks != 0 && clickedMine == 0) {
                    tiles[j].at(i).tile.setPosition(sf::Vector2f(tiles[j].at(i).minimumX, tiles[j].at(i).minimumY));
                    window.draw(tiles[j].at(i).tile);
                    if (tiles[j].at(i).flag == 1) {
                        MiscelaneousButtons flag1("flag", flag, (tiles[j].at(i).minimumX), (tiles[j].at(i).minimumY));
                        flag1.Misc.setPosition(sf::Vector2f(flag1.buttonXMin, flag1.buttonYMin));
                        window.draw(flag1.Misc);

                        if (done == 1) {
                            tempMineCount--;
                            done = 0;
                        }
                        else if (done == 2) {
                            tempMineCount++;
                            done = 0;
                        }
                    }
                    if (tiles[j].at(i).mineOrNot == '1') {
                        Mines mine(mineTexture, (tiles[j].at(i).minimumX), (tiles[j].at(i).minimumY));
                        mine.mines1.setPosition(sf::Vector2f(mine.x, mine.y));
                        window.draw(mine.mines1);
                    }
                    if ((tiles[j].at(i).mineCount != 0)) {
                        sf::Sprite singleNumber = numbers.at(tiles[j].at(i).mineCount - 1);
                        singleNumber.setPosition(sf::Vector2f(tiles[j].at(i).minimumX, tiles[j].at(i).minimumY));
                        window.draw(singleNumber);
                    }

                }
                // lose or win???
                else if ((tiles[j].at(i).revealed == 1 && tiles[j].at(i).mineOrNot == '1') || streaks == 0) {
                   //WIN yayyyy!!! =)
                    if (streaks == 0) {
                        for (int m = 0; m < stoi(rows); ++m) {
                            for (int n = 0; n < stoi(columns) ; ++n) {
                                //if it's a mine, gets flagged and does not get revealed
                                if(tiles[m].at(n).mineOrNot == '1') {
                                    //flags all mines
                                    tiles[m].at(n).tile.setTexture(Texture::GetTexture("tile_hidden"));
                                    tiles[m].at(n).tile.setPosition(sf::Vector2f(tiles[m].at(n).minimumX, tiles[m].at(n).minimumY));
                                    window.draw(tiles[m].at(n).tile);
                                    MiscelaneousButtons flag1("flag", flag, (tiles[m].at(n).minimumX), (tiles[m].at(n).minimumY));
                                    flag1.Misc.setPosition(sf::Vector2f(flag1.buttonXMin, flag1.buttonYMin));
                                    window.draw(flag1.Misc);
                                }
                                //if normal reveals, with number if applicable
                                else {
                                    //reveals all other tiles
                                    window.draw(tiles[m].at(n).tile);
                                    if ((tiles[m].at(n).mineCount != 0)) {
                                        sf::Sprite singleNumber = numbers.at(tiles[m].at(n).mineCount - 1);
                                        singleNumber.setPosition(sf::Vector2f(tiles[m].at(n).minimumX, tiles[m].at(n).minimumY));
                                        window.draw(singleNumber);
                                    }
                                }
                            }
                        }
                        otherButtons.at(0).Misc.setTexture(Texture::GetTexture("face_win"));
                        window.draw(winSmiley);
                        tempMineCount = 0;
                        loseOrWin = true;
                        endGame = 1;
                        debug1 = 0;
                    }
                    //lose =(
                    else {
                        for (int k = 0; k < stoi(rows); ++k) {
                            for (int l = 0; l < stoi(columns); ++l) {
                                if (tiles[k].at(l).mineOrNot == '1') {
                                    // reveals all mines
                                    tiles[k].at(l).tile.setTexture(Texture::GetTexture("tile_revealed"));
                                    tiles[k].at(l).tile.setPosition(sf::Vector2f(tiles[k].at(l).minimumX, tiles[k].at(l).minimumY));
                                    window.draw(tiles[k].at(l).tile);
                                    Mines mine(mineTexture, (tiles[k].at(l).minimumX), (tiles[k].at(l).minimumY));
                                    mine.mines1.setPosition(sf::Vector2f(mine.x, mine.y));
                                    window.draw(mine.mines1);
                                }
                                else {
                                    //prints all tiles as they were
                                    tiles[k].at(l).tile.setPosition(sf::Vector2f(tiles[k].at(l).minimumX, tiles[k].at(l).minimumY));
                                    window.draw(tiles[k].at(l).tile);
                                    //reveals all other tiles
                                    if ((tiles[k].at(l).mineCount != 0) && tiles[k].at(l).revealed == 1) {
                                        sf::Sprite singleNumber = numbers.at(tiles[k].at(l).mineCount - 1);
                                        singleNumber.setPosition(sf::Vector2f(tiles[k].at(l).minimumX, tiles[k].at(l).minimumY));
                                        window.draw(singleNumber);
                                    }
                                }
                            }
                        }
                        otherButtons.at(0).Misc.setTexture(Texture::GetTexture("face_lose"));
                        window.draw(loseSmiley);
                        loseOrWin = false;
                        endGame = 1;
                        tempMineCount = tempMineCount2;
                        debug1 = 0;
                    }
                    break;
                }
                //regular mode
                else if (streaks != 0 && endGame == 0) {
                    tiles[j].at(i).tile.setPosition(sf::Vector2f(tiles[j].at(i).minimumX, tiles[j].at(i).minimumY));
                    window.draw(tiles[j].at(i).tile);
                    if (tiles[j].at(i).flag == 1 && tiles[j].at(i).revealed == 0) {
                        MiscelaneousButtons flag1("flag", flag, (tiles[j].at(i).minimumX), (tiles[j].at(i).minimumY));
                        flag1.Misc.setPosition(sf::Vector2f(flag1.buttonXMin, flag1.buttonYMin));
                        window.draw(flag1.Misc);
                        if (done == 1) {
                            tempMineCount--;
                            done = 0;
                        }
                    }
                    else if (tiles[j].at(i).revealed == 1) {
                        if ((tiles[j].at(i).mineCount != 0)) {
                            for (int k = 0; k < tiles[j].at(i).mineCount; ++k) {
                                sf::Sprite singleNumber = numbers.at(tiles[j].at(i).mineCount - 1);
                                singleNumber.setPosition(sf::Vector2f(tiles[j].at(i).minimumX, tiles[j].at(i).minimumY));
                                window.draw(singleNumber);
                            }
                        }
                    }
                    otherButtons.at(0).Misc.setTexture(Texture::GetTexture("face_happy"));
                }
                if (done == 2) {
                        tempMineCount++;
                        done = 0;
                }
            }
        }

        //draws the random buttons
        for (int i = 0; i < otherButtons.size(); ++i) {
            if (i == 0 && endGame == 0) {
                otherButtons.at(i) = MiscelaneousButtons(name, mrSmiley, (halfWidth - 32), yNumber);
                window.draw(mrSmiley);
            }
            else if (i == 0 && endGame == 1) {
                if (loseOrWin == true) {
                    otherButtons.at(i) = MiscelaneousButtons(name, winSmiley, (halfWidth - 32), yNumber);
                    window.draw(otherButtons.at(i).Misc);
                }
                else {
                    otherButtons.at(i) = MiscelaneousButtons(name, loseSmiley, (halfWidth - 32), yNumber);
                    window.draw(otherButtons.at(i).Misc);
                }
            }
            else {
                otherButtons.at(i).Misc.setPosition(sf::Vector2f(otherButtons.at(i).buttonXMin, yNumber));
                window.draw(otherButtons.at(i).Misc);
            }
        }

        //draw current number of mines
        DrawDigit(tempMineCount, digits, stoi(rows), window);



        sf::Event event;
        while (window.pollEvent(event)) {
            int leftOrRight = 0;
            /*********************************** Mouse Event ********************************/
            if (event.type == sf::Event::MouseButtonPressed) {
                //left mouse button is pressed
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i localPosition;
                    leftOrRight = 0;
                    localPosition = sf::Mouse::getPosition(window);
                    //location of left mouse button is within range of location tiles
                    if (localPosition.y <= (maxYHidden) && (localPosition.x >= 0 && localPosition.x <= width)) {
                        cout << "less" << endl;
                        //look for which tile
                        for (int j = 0; j < stoi(rows); ++j) {
                            for (int i = 0; i < stoi(columns); ++i) {
                                if ((localPosition.x >= tiles[j].at(i).minimumX &&
                                     localPosition.x <= tiles[j].at(i).maximumX) &&
                                    (localPosition.y >= tiles[j].at(i).minimumY &&
                                     localPosition.y <= tiles[j].at(i).maximumY)) {
                                    cout << j << i << endl;
                                    //if the game is not over, reveals tile
                                    if (endGame != 1) {
                                        //if it's not a mines, reveals the tile recursively
                                        if (tiles[j].at(i).flag == 0 && tiles[j].at(i).mineOrNot == '0') {
                                            RevealTileRecursive(tiles[j].at(i), stoi(rows), stoi(columns), hiddenTile,
                                                                numbers);
                                            for (int k = 0; k < stoi(rows); ++k) {
                                                for (int j = 0; j < stoi(columns); ++j) {
                                                    //if tile was flagged, resets tile to flagged state
                                                    if (tiles[k].at(j).flag == 1) {
                                                        tiles[k].at(j).revealed = 0;
                                                        tiles[k].at(j).tile.setTexture(
                                                                Texture::GetTexture("tile_hidden"));
                                                    }
                                                }
                                            }
                                            tiles[j].at(i).tile.setTexture(Texture::GetTexture("tile_revealed"));
                                            tiles[j].at(i).revealed = 1;
                                        }
                                        //if it's a mine reveals that singular tile
                                        else if (tiles[j].at(i).mineOrNot == '1' && tiles[j].at(i).flag == 0) {
                                            tiles[j].at(i).tile.setTexture(Texture::GetTexture("tile_revealed"));
                                            tiles[j].at(i).revealed = 1;
                                            clickedMine = 1;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    //location of left mouse button is within range of the other buttons
                    else if (localPosition.y > (maxYHidden) && localPosition.y <= ((maxYHidden + 64)) && (localPosition.x >= 0 && localPosition.x <= width)) {
                        cout << "more" << endl;
                        //look for x
                        for (int i = 0; i < otherButtons.size(); ++i) {
                            if(localPosition.x >= otherButtons.at(i).buttonXMin && localPosition.x <= otherButtons.at(i).buttonXMax) {
                                //if it's a test button, reads test file, creates a new board with new data from test file
                                if (i > 1 && (i <= 4)) {
                                    tempMineCount = 0;
                                    tempMineCount2 = 0;
                                    tiles = CreateTile(stoi(rows), stoi(columns), hiddenTile, mineCount);
                                    endGame = 0;
                                    LoadTest(i - 1, tiles, stoi(rows), tempMineCount, tempMineCount2);
                                    clickedMine = 0;
                                    CreateAdjacentTile(tiles, stoi(rows), stoi(columns));
                                }
                                //if it's mr.Smiley, resets game board with new data
                                else if (i == 0) {
                                    tiles = CreateTile(stoi(rows), stoi(columns), hiddenTile, mineCount);
                                    CreateAdjacentTile(tiles, stoi(rows), stoi(columns));
                                    endGame = 0;
                                    tempMineCount = mineCount;
                                    clickedMine = 0;
                                }
                                //if it's the debug button, sets it to opposite current mode
                                else if (endGame == 0) {
                                    if(debug1 == false) {
                                        debug1 = true;
                                    }
                                    else {
                                        debug1 = false;
                                    }
                                }
                            }
                        }
                    }
                    cout << localPosition.x << " " << localPosition.y << endl;
                }
                //right mouse button is pressed
                if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i localPosition;
                    leftOrRight = 0;
                    localPosition = sf::Mouse::getPosition(window);
                    //location of right mouse button is within range of location tiles
                    if (localPosition.y <= (maxYHidden) && (localPosition.x >= 0 && localPosition.x <= width)) {
                        cout << "less" << endl;
                        cout << localPosition.x << " " << localPosition.y << endl;
                        //look for tile
                        done = 0;
                        //look for which tile
                        for (int j = 0; j < stoi(rows); ++j) {
                            for (int i = 0; i < stoi(columns); ++i) {
                                if((localPosition.x >= tiles[j].at(i).minimumX &&
                                localPosition.x <= tiles[j].at(i).maximumX) &&
                                (localPosition.y >= tiles[j].at(i).minimumY &&
                                localPosition.y <= tiles[j].at(i).maximumY)) {
                                    cout << i << endl;
                                    if (endGame == 0) {
                                        //if tile was not flagged, flags it
                                        if (tiles[j].at(i).flag == 0) {
                                            tiles[j].at(i).flag = 1;
                                            cout << "flag" << endl;
                                            done = 1;
                                        }
                                            //if tile was flagged, removes its flag it
                                        else {
                                            tiles[j].at(i).flag = 0;
                                            cout << "unflag" << endl;
                                            done = 2;
                                        }
                                    }
                                    break;
                                }
                            }
                            //keeps count how many tiles are flagged, and is used to update mine count
                            if (done == 1 || done == 2) {
                                break;
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.display();

    }
        Texture::clear();
    return 0;
}
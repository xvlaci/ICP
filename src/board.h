#ifndef BOARD_H
#define BOARD_H


#include <iostream>
#include <string>
#include "square.h"



class Board{
private:
    int width;
    int height;
    std::string map;
    Square *** board;
    void loadMap();
    char symbols[7];
public:
    Board(int width, int height, std::string map);
    ~Board();

    Square * getSquare(int x, int y);
    std::string generateMsg();
    void printMap();

    Square * player_start_pos[4];

};

#endif // BOARD_H

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
public:
    Board(int width, int height, std::string map);
    ~Board();

    Square * getSquare(int x, int y);
    std::string generateMsg();
    void printMap();
};

#endif // BOARD_H

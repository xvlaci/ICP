/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include "square.h"

class Board{
private:
    void loadMap();
    int width;
    int height;
    std::string map;
    Square *** board;
    char symbols[14];
public:
    Board(int width, int height, std::string map);
    ~Board();
    int getWidth();
    int getHeight();
    Square * getSquare(int x, int y);

    std::string generateMsg();
    void printMap();

    Square * player_start_pos[4];
    Square * guards_pos[20];
    int guards;
};

#endif // BOARD_H

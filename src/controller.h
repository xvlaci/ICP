#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "board.h"

using namespace std;

struct maze_map{
    int width;
    int height;
    string maze;
};

class Controller{
private:
    string status;
    Board * b;
    void newCoords(int & x, int & y, int facing);
public:
    Controller();
    ~Controller();
    void setBoard(Board * b);

    Square * move(Square * s);
    void moveGuard();
    Square * turn(Square * s, int dir);
    Square * pickUpKey(Square * s);
    Square * openGate(Square * s);

    Board * getBoard();
    string getStatusMessage();

    maze_map load(string filename);
};

#endif // CONTROLLER_H

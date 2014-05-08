#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "board.h"

using namespace std;

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
};

#endif // CONTROLLER_H

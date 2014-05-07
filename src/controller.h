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
public:
    Controller();
    ~Controller();
    void setBoard(Board * b);

    Square * move(Square * s);
    Square * moveGuard(Square * s);
    Square * turn(Square * s, int dir);

    Board * getBoard();
    string getStatusMessage();
};

#endif // CONTROLLER_H

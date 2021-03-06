/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "controller.h"
#include "board.h"
#include <ctime> // Needed for the true randomization
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

Controller::Controller(){}

Square * Controller::move(Square * s)
{

    if(s->getObjectType() != PLAYER)
        return 0;

    int x = s->getX();
    int y = s->getY();
    s->getCharacter()->alive = true;
    this->newCoords(x, y, s->getCharacter()->facing());

    Square * new_s = this->b->getSquare(x,y);
    //std::cout << new_s->getX() << " x " << new_s->getY() << std::endl;
    //std::cout << new_s->getObjectType() << std::endl;

    if(new_s->getObjectType() == EMPTY){
        new_s->setCharacter(s->getCharacter());
        new_s->setObjectType(PLAYER);
        s->clearSquare();
        return new_s;
    }
    else if(new_s->getObjectType() == GUARD)
    {
        s->clearSquare();
        return 0;
    }
    else if(new_s->getObjectType() == FINISH)
    {
        return new_s;
    }
    else{
        return s;
    }
}

void Controller::newCoords(int & x, int & y, int facing)
{
    switch(facing){
        case UP:
            y--;
            break;
        case RIGHT:
            x++;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
    }
}

Square * Controller::pickUpKey(Square * s)
{
    if(s->getObjectType() != PLAYER)
        return 0;

    int x = s->getX();
    int y = s->getY();

    this->newCoords(x, y, s->getCharacter()->facing());

    Square * new_s = this->b->getSquare(x,y);

    if(new_s->getObjectType() == KEY){
        new_s->clearSquare();
        s->getCharacter()->pickUpKey();
        return s;
    }
    return s;
}

Square * Controller::openGate(Square * s)
{
    if(s->getObjectType() != PLAYER)
        return 0;

    int x = s->getX();
    int y = s->getY();

    this->newCoords(x, y, s->getCharacter()->facing());

    Square * new_s = this->b->getSquare(x,y);

    if(new_s->getObjectType() == GATE && s->getCharacter()->hasKey()){
        new_s->clearSquare();
        s->getCharacter()->useKey();
        return s;
    }
    return s;
}

void Controller::moveGuard()
{
    int rn;
    int x, y;
    Square * guard;
    for(int i = 0; i < this->b->guards; i++){

        guard = this->b->guards_pos[i];
        x = guard->getX();
        y = guard->getY();
        int tries = 5;

        while(tries > 0){
            rn = rand() % 100 + 1;
            int new_x = x;
            int new_y = y;

            if(rn <= 70){
                newCoords(new_x, new_y, guard->getCharacter()->facing());
                Square * new_s = this->b->getSquare(new_x, new_y);

                if(new_s->getObjectType() == EMPTY || \
                   (new_s->getObjectType() == PLAYER && new_s->getCharacter()->alive)){
                    tries = 0;
                    new_s->setCharacter(guard->getCharacter());
                    new_s->setObjectType(GUARD);
                    this->b->guards_pos[i]->clearSquare();
                    this->b->guards_pos[i] = new_s;
                    if(new_s->getObjectType() == PLAYER){
                        new_s->getCharacter()->living = false;
                    }
                }
            }
            else if(rn < 80){
                guard->getCharacter()->turn(guard->getCharacter()->facing()-1);
                tries = 0;
            }
            else if(rn < 90){
                guard->getCharacter()->turn(guard->getCharacter()->facing()+1);
                tries = 0;
            }
            else{
                guard->getCharacter()->turn(guard->getCharacter()->facing()-2);
                tries = 0;
            }
        }
    }
}

Square * Controller::turn(Square * s, int dir)
{
    if(s->getObjectType() != PLAYER){
        return 0;
    }

    s->getCharacter()->turn(dir);

    return s;
}

Board * Controller::getBoard()
{
    return this->b;
}


void Controller::setBoard(Board * b)
{
    this->b = b;
}



maze_map Controller::load(string filename)
{
    ifstream f;
    f.open(filename.c_str());
    string line;
    string maze;
    string width;
    string height;
    if (f.is_open()) {
        getline(f,width);
        getline(f,height);
        while(getline(f,line))
            maze.append(line);
    }
    f.close();

    maze_map tmp_maze_map = { atoi(width.c_str()), atoi(height.c_str()), maze};

    return tmp_maze_map;
}

void Controller::save(string filename)
{
    using namespace std;
    filename.append(".map");
    ofstream f;
    string msg = b->generateMsg();

    f.open(filename.c_str());
    if (f.is_open()) {
        f << msg;
    }
    f.close();
}


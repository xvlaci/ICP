#include "controller.h"
#include "board.h"



Controller::Controller(){}

Square * Controller::move(Square * s){

    if(s->getObjectType() != PLAYER)
        return 0;

    int x = s->getX();
    int y = s->getY();

    switch(s->getCharacter()->facing()){
        case UP:
            y++;
            break;
        case RIGHT:
            x++;
            break;
        case DOWN:
            y--;
            break;
        case LEFT:
            x--;
            break;
    }

    Square * new_s = this->b->getSquare(x,y);

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
    else{
        return s;
    }
}

Square * Controller::turn(Square * s, int dir){
    if(s->getObjectType() != PLAYER){
        return 0;
    }

    s->getCharacter()->turn(dir);

    return s;
}

Board * Controller::getBoard(){
    return this->b;
}


void Controller::setBoard(Board * b){
    this->b = b;
}

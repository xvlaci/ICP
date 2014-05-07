#include "square.h"

Square::Square(int x, int y, int object_type){
    this->x = x;
    this->y = y;
    this->object_type = object_type;
    if(object_type == GUARD){
        this->character = new Character(false, UP);
    }
    if(object_type == PLAYER){
        this->character = new Character(true, UP);
    }
}

Character * Square::getCharacter(){
    return this->character;
}

void Square::setCharacter(Character * character){
    this->character = character;
}

int Square::getObjectType(){
    return this->object_type;
}

void Square::setObjectType(int type){
    this->object_type = type;
}

void Square::clearSquare(){
    this->character = 0;
    this->object_type = EMPTY;
}

int Square::getX(){
    return this->x;
}

int Square::getY(){
    return this->y;
}

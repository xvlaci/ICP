#include "square.h"

Square::Square(int x, int y, int object_type){
    this->x = x;
    this->y = y;
    this->object_type = object_type;
    if(object_type == GUARD){
        this->character = new Character(false, UP);
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

void Square::clearSquare(){
    this->character = 0;
    this->object_type = 0;
}

int Square::getX(){
    return this->x;
}

int Square::getY(){
    return this->y;
}

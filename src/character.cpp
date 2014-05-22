/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "character.h"

Character::Character(bool player, int direction){
    this->key = false;
    this->player = player;
    this->direction = direction;
    this->alive = false;
    this->color = 0;
}


bool Character::hasKey(){
    return this->key;
}

void Character::useKey(){
    this->key = false;
}

void Character::pickUpKey(){
    this->key = true;
}

bool Character::isPlayer(){
    return this->player;
}

void Character::turn(int side){
    this->direction = (side + 4) % 4;
}

int Character::facing(){
    return this->direction;
}

int Character::getColor(){
    return this->color;
}

void Character::setColor(int color){
    this->color = color;
}

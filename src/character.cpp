#include "character.h"

Character::Character(bool player, int direction){
    this->key = false;
    this->player = player;
    this->direction = direction;
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

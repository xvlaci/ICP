/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#include "square.h"

Square::Square(int x, int y, int object_type)
{
    this->x = x;
    this->y = y;
    this->object_type = object_type;
    object_type += '0';

    if(object_type >= 'e' && object_type <= 'h'){
        this->object_type = PLAYER;
        this->character = new Character(true, object_type - 'e');
    }

    if(object_type >= 'a' && object_type <= 'd'){
        this->object_type = GUARD;
        this->character = new Character(false, object_type - 'a');
    }
}

Character * Square::getCharacter()
{
    return this->character;
}

void Square::setCharacter(Character * character)
{
    this->character = character;
}

int Square::getObjectType()
{
    return this->object_type;
}

void Square::setObjectType(int type)
{
    this->object_type = type;
}

void Square::clearSquare()
{
    this->character = 0;
    this->object_type = EMPTY;
}

int Square::getX()
{
    return this->x;
}

int Square::getY()
{
    return this->y;
}

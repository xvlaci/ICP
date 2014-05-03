#ifndef SQUARE_H
#define SQUARE_H

#include <character.h>

enum {
    EMPTY = 0,
    WALL,
    GATE,
    KEY,
    GUARD,
    PLAYER
};

class Square{
private:
    int x;
    int y;
    int object_type;
    Character * character;
public:
    Square(int x, int y, int object_type);
    ~Square();
    Character * getCharacter();
    void setCharacter(Character * character);
    void clearSquare();
    int getX();
    int getY();
};

#endif // SQUARE_H

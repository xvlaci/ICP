/**
@author Martin Vlacil - xvlaci00@stud.fit.vutbr.cz
@author Jan Sedo      - xsedoj00@stud.fit.vutbr.cz
*/


#ifndef CHARACTER_H
#define CHARACTER_H

enum {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

class Character {
private:
    bool key;
    bool player;
    int direction;
    int color;
public:
    Character(bool player, int direction);
    ~Character();
    bool hasKey();
    void useKey();
    void pickUpKey();
    int getColor();
    void setColor(int color);
    bool isPlayer();
    void turn(int side);
    int facing();

    bool living;
    bool alive;
};

#endif // CHARACTER_H

#ifndef CHARACTER_H
#define CHARACTER_H

enum {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

class Character {
private:
    bool key;
    bool player;
    int direction;
public:
    Character(bool player, int direction);
    ~Character();
    bool hasKey();
    void useKey();
    void pickUpKey();

    bool isPlayer();
    void turn(int side);
    int facing();
};

#endif // CHARACTER_H
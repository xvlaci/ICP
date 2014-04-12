#ifndef GAME_H
#define GAME_H
#include <QObject>

#include "board.h"

class Game : public QObject
{
    Q_OBJECT

public:
    static Game *getInstance();

    virtual ~Game(void);

private:

    static Game *game;

    Board *board;

    explicit Game(QObject *parent = 0);

signals:

public slots:

    bool startGameSlot();

};

#endif // GAME_H

#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPoint>
#include <QGraphicsScene>

//#include "element.h"

class Board : public QObject
{
    Q_OBJECT

public:

    /**
      * Vytvori hraci pole.
      * @param parent Ukazatel na rodice.
      */
    explicit Board(QObject * parent = 0);

    /**
      * Znici hraci pole.
      */
    virtual ~Board(void);

    void paintBoard();

private:

    int * neco[8][8];
    //Element * board[8][8];

signals:

};


#endif // BOARD_H

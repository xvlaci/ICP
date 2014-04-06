#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPoint>

#include "element.h"

//class King;
//class Queen;
//class Bishop;
//class Knight;
//class Pawn;
//class Rook;

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

    //bool isEmpty(QPoint target);
    //void addPiece(APiece * piece);
    //bool isMoveValid(QPoint source, QPoint target);
    //void movePiece(QPoint source, QPoint target);
    //APiece * getPiece(QPoint coordinates);

private:

    /**
      *
      */
    Element * board[8][8];

//signals:

};


#endif // BOARD_H

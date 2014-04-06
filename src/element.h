#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QPoint>

#include "player.h"
#include "sentry.h"
#include "object.h"

/**
  * Abstraktní figurka. Obsahuje implementaci zakladnich figurek,
  * ovsem ma i ciste virtualni metody, ktere je treba doimplementovat
  * v jednotlivych figurkach.
  */

class Element: public QObject
{
    Q_OBJECT

public:

    /**
      * Konstruktor figury.
      * @param color Barva figurky. True = bila, false = cerna.
      * @param coordinate Souradnice, na kterych je figurka na sachovnici.
      * @param * parent Ukazatel na rodice.
      */
    explicit Element(QObject * parent = 0);

    /**
      * Desktruktor figury.
      */
    virtual ~Element(void);

    /**
      * Rozhodne, zda je tah validni.
      * @param * chessboard Sachovnice, na ktere se ma tah provest.
      * @param target Souradnice, na kterou se ma figura presunout.
      * @return True = tah je validni. False = tah neni validni.
      *
    virtual bool isMoveValid(Chessboard * chessboard, QPoint & target) = 0;

    **
      * Vrati nactenou SVG ikonu k vykresleni.
      * @return SVG ikona pripravena k vykresleni.
      *
    virtual QSvgRenderer * getIcon(void);

    **
      * Vrati souradnice pole, na kterem je figura.
      * @return Souřadnice figury.
      *
    QPoint & getCoordinate();

    void setCoordinate(QPoint point) {
        coordinate = point;
    }

    bool getColor()
    {
        return color;
    }*/


protected:

    /**
      * Barva figurky. True = bila, false = cerna.
      */
    bool color;

    /**
      * Pozice figury.
      *
    QPoint coordinate;

    **
      * Ikona figury.
      *
    QSvgRenderer * icon;*/
};


#endif // ELEMENT_H

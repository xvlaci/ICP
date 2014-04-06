#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>
#include <QDebug>

/**
  * Kreslitko na platno.
  */

class Painter : public QPainter
{
public:

    /**
      * Vytvoreni kreslitka.
      */
    explicit Painter(void);

    /**
      * Zniceni kreslitka.
      */
    virtual ~Painter(void);

    /**
      * Nakresleni sachovnice.
      */
    void drawBoard(void);

};



#endif // PAINTER_H

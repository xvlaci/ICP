#include "painter.h"

Painter::Painter() : QPainter()
{

}

Painter::~Painter()
{

}

void Painter::drawBoard()
{
    // Ulozi se stav kvuli transformacim.
    save();

    bool color = true;
    int size = (viewport().width() / 8.3);
    setPen(Qt::black);

    for (int y = 0; y < 8; y++) {
        // Pridavani ocislovani radku.
        drawText(0, 0, size / 3, size, Qt::AlignCenter, QString::number(8-y));
        translate(size / 3, 0);
        for (int x = 0; x < 8; x++) {
            if (color) {
                setBrush(Qt::white);
            } else {
                setBrush(QColor::fromRgb(100, 100, 100));
            }
            drawRect(0, 0, size, size);
            translate(size, 0);
            color = !color;
            size = (viewport().width() / 8.3);
        }
        color = !color;
        translate(-(size*8 + size/3), size);
    }


    setBrush(Qt::blue);
    setPen(Qt::black);
    translate(size / 3, 0);

    // Prida se radka s pismeny.
    for (int i = 0; i < 8; i++) {
        drawText(0, 0, size, size / 3, Qt::AlignCenter, QString((char) 65 + i));
        translate(size, 0);
    }

    // Obnovi se stav transformaci.
    restore();
}

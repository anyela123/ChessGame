#ifndef HORSE_H
#define HORSE_H

#include "piece.h"
class Horse:public Piece
{
public:
    Horse(QString team,QGraphicsItem *parent = 0);
    void setImage();

    void move();

};

#endif // HORSE_H

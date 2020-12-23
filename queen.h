#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
class Queen:public Piece
{
public:
    Queen(QString team,QGraphicsItem *parent = 0);
    void setImage();

    void move();

};

#endif // QUEEN_H

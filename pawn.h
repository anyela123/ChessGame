#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
class Pawn:public Piece
{
public:
    Pawn(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void move();

 private:


};

#endif // PAWN_H

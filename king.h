#ifndef KING_H
#define KING_H

#include "piece.h"
class King:public Piece
{
public:
    King(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void findUnSafeLocation();
    void move();

};

#endif // KING_H

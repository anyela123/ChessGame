#ifndef TOWER_H
#define TOWER_H
#include "piece.h"
class Tower:public Piece
{
public:
    Tower(QString team, QGraphicsItem *parent = 0);

    void setImage();
    void move();

};

#endif // TOWER_H

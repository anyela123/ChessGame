#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include "Cell.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
struct Move_piece{
   QString origin;
   QString destiny;
   QString name=" ";
};
class Cell;
class Piece:public QGraphicsPixmapItem
{
public:
    Piece(QString team = "",QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentCell(Cell *Cell);
    Cell *getCurrentCell() ;
    QString getSide() ;
    void setSide( QString value);
    virtual void setImage() = 0;
    bool getMoved() ;
    void setMoved(bool value);
    QList <Cell *> moveLocation();
    virtual void move() = 0;
    void recolor();
    bool firstMove;
    bool CellSetup(Cell *Cell);
    Move_piece control;
protected:
    Cell *currentCell;
    QString side;
    bool Moved;
    QList <Cell *> location;
    QString name;

};

#endif // CHESSPIECE_H

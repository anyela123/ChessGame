#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include "Locker.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
struct Move_piece{
   QString origin;
   QString destiny;
   QString name=" ";
};
class ChessCell;
class Piece:public QGraphicsPixmapItem
{
public:
    Piece(QString team = "",QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentCell(ChessCell *Cell);
    ChessCell *getCurrentCell() ;
    QString getSide() ;
    void setSide( QString value);
    virtual void setImage() = 0;
    bool getMoved() ;
    void setMoved(bool value);
    QList <ChessCell *> moveLocation();
    virtual void move() = 0;
    void recolor();
    bool firstMove;
    bool CellSetup(ChessCell *Cell);
    Move_piece control;
protected:
    ChessCell *currentCell;
    QString side;
    bool Moved;
    QList <ChessCell *> location;
    QString name;

};

#endif // CHESSPIECE_H

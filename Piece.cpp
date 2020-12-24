#include "piece.h"
#include "juego.h"
#include <QDebug>
#include <memory>
#include "king.h"
#include <QColor>

extern Juego *juego;

Piece::Piece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    Moved = true;
    firstMove = true;
}
//evento al presionar una chesspiece
void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == juego->pieceToMove){
        juego->pieceToMove->getCurrentCell()->resetOriginalColor();
        juego->pieceToMove->recolor();
        juego->pieceToMove = NULL;
       return;
    }
    //para saber si ya paso su turno
    if((!getMoved() )|| ( (juego->getTurn() != this->getSide())&& (!juego->pieceToMove)) )
        return;
    if(!juego->pieceToMove){

        juego->pieceToMove = this;
        juego->pieceToMove->getCurrentCell()->setColor(QColor(247,69,10)); // color posicion pieza
        juego->pieceToMove->move();
    }
    else if(this->getSide() != juego->pieceToMove->getSide()){
        this->getCurrentCell()->mousePressEvent(event);
    }


}
/*Cambia la celda actual en donde se encuentra el obj*/
void Piece::setCurrentCell(Cell *Cell)
{

    currentCell = Cell;
}
/*Obtiene la celda actual en donde se encuentra el obj*/
Cell *Piece::getCurrentCell()
{
    return currentCell;
}
/*obtiene el bando (equipo) donde se encuentra black or white*/
QString Piece::getSide()
{
    return side;
}
/*asigna el bando (equipo) donde se encuentra black or white*/
void Piece::setSide( QString value)
{
    side = value;
}

//retornamos el valor moved
bool Piece::getMoved()
{
    return Moved;
}

//cambiamos el valor de moved
void Piece::setMoved(bool value)
{
    Moved = value;

}

//retornamos la location en la que estamos
QList<Cell *> Piece::moveLocation()
{
    return location;
}

//reseteamos el color
void Piece::recolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}


bool Piece::CellSetup(Cell *Cell)
{
    if(Cell->getHasChessPiece()) {
        King *q = dynamic_cast<King*>(location.last()->currentPiece);
        if(q){
            Cell->setColor(Qt::blue);
        }
        else
            Cell->setColor(Qt::yellow); // muestra cual comer
        return true;
    }
    else
        location.last()->setColor(Qt::darkRed);
    return false;
}




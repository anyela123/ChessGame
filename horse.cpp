#include "horse.h"
#include "juego.h"
extern Juego *juego;
Horse::Horse(QString team,QGraphicsItem *parent):Piece(team,parent)
{
    name="C";
    //se inicializa poniendo su imagen
    setImage();
}
/*Se encarga de colocar la imagen al objeto mediante Qpixmap*/

void Horse::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/img/img/horse_w.png"));
    else
        setPixmap(QPixmap(":/img/img/horse_b.png"));
}
/*Se encarga de como se mueve la pieza*/

void Horse::move()
{
    int row = this->getCurrentCell()->rowLoc;
    int col = this->getCurrentCell()->colLoc;
    int i ,j;
    QString team  = this->getSide();

    //Hay 8 formas de mover al caballo
    // tomando en cuenta WASD como instrucciones
    //1st w w a
    i = row - 2;
    j = col - 1;
    if(i >=1 && j>=1 && (juego->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(juego->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }

    //2nd w w d
    i = row - 2;
    j = col + 1;
    if(i >=1 && j<=8 && (juego->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(juego->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }

    //3rd s s a
    i = row + 2;
    j = col - 1;
    if(i <= 8 && j>=1 && (juego->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(juego->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }

    //4th  s s d
    i = row + 2;
    j = col + 1;
    if(i <=8 && j<=8 && (juego->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(juego->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }

    //5th a a w
    i = row - 1;
    j = col - 2;
    if(i >=1 && j>=1 && (juego->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(juego->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }

    //6th a a s
    i = row + 1;
    j = col - 2;
    if(i <=8 && j>=1 && (juego->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(juego->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }

    //7th d d w
    i = row - 1;
    j = col + 2;
    if(i >=1 && j<=8 && (juego->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(juego->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }

    //8th d d s
    i = row + 1;
    j = col +  2;
    if(i <=8 && j<=8 && (juego->collection[i][j]->getChessPieceColor() != team) ) {
        location.append(juego->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }

}


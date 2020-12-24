#include "king.h"
#include "pawn.h"
#include "juego.h"
extern Juego *juego;
King::King(QString team,QGraphicsItem *parent):Piece(team,parent)
{
    name="R";
    //se inicializa poniendo su imagen
    setImage();
}
/*Se encarga de colocar la imagen al objeto mediante Qpixmap*/

void King::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/img/img/king_w.png"));
    else
        setPixmap(QPixmap(":/img/img/king_b.png"));
}

/*Se encarga de como se mueve la pieza*/

void King::move()
{

    location.clear();
    int row = this->getCurrentCell()->rowLoc;
    int col = this->getCurrentCell()->colLoc;
    QString team = this->getSide();

        if(col > 1 && row > 1 && !(juego->collection[row-1][col-1]->getChessPieceColor() == team)) {//up left
            location.append(juego->collection[row-1][col-1]);
            juego->collection[row-1][col-1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col < 8 && row > 1 && !(juego->collection[row-1][col+1]->getChessPieceColor() == team)) { // up right
            location.append(juego->collection[row-1][col+1]);
            juego->collection[row-1][col+1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(row>1 && !(juego->collection[row-1][col]->getChessPieceColor() == team)) {//up
            location.append(juego->collection[row-1][col]);
            juego->collection[row-1][col]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(row<8 && !(juego->collection[row+1][col]->getChessPieceColor() == team)) {//down
            location.append(juego->collection[row+1][col]);
            juego->collection[row+1][col]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col>1 && !(juego->collection[row][col-1]->getChessPieceColor() == team)) {// left
            location.append(juego->collection[row][col-1]);
            juego->collection[row][col-1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col<8 && !(juego->collection[row][col+1]->getChessPieceColor() == team)) {//right
            location.append(juego->collection[row][col+1]);
            juego->collection[row][col+1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col > 1 && row < 8  && !(juego->collection[row+1][col-1]->getChessPieceColor() == team)) {//down left
            location.append(juego->collection[row+1][col-1]);
            juego->collection[row+1][col-1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col < 8 && row < 8 && !(juego->collection[row+1][col+1]->getChessPieceColor() == team)) {//down right
            location.append(juego->collection[row+1][col+1]);
            juego->collection[row+1][col+1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }


            findUnSafeLocation();

}
/*se encarga de realizar un check para ver si el rey se encuentra en jaque*/
void King::findUnSafeLocation() {
    QList <Piece *> pList = juego->piecesInGame;
    for(size_t i = 0,n = pList.size(); i < n; i++) {

        if(pList[i]->getSide() != this->getSide())
        {
            QList <Cell *> bList = pList[i]->moveLocation();

            for(size_t j = 0, n = bList.size(); j < n; j++) {
                Pawn *c = dynamic_cast<Pawn *> (pList[i]) ;
                if(c)
                    continue;
                for(size_t k = 0, n = location.size(); k < n; k++) {
                   if(bList[j] == location [k]) {
                       location[k]->setColor(Qt::blue);
                   }
                }
            }
        }
    }
}

#include "Cell.h"
#include "juego.h"
#include <memory>
#include <QDebug>
#include "king.h"
#include <QLabel>
#include <QMessageBox>

extern Juego *juego;
Cell::Cell(QString text,QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //dibujar la celda
    setRect(0,0,80,80);//rectangulo
                                                                                //QPainter *painter=new QPainter();
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");

    currentPiece = NULL;
}

Cell::~Cell()
{
    delete this;
}
void Cell::setText(QString text){
    texto = new QGraphicsTextItem(text, this);
    int xPos = rect().width()/2 - texto->boundingRect().width()/2;
    int yPos = rect().height()/2 - texto->boundingRect().height()/2;
    texto->setZValue(0.1);//valor de celda... no forma parte del tablero de juego
    texto->setDefaultTextColor(Qt::black);//color de indices a,b,cd ...
    texto->setFont(QFont("",12));
    texto->setPos(xPos-10,20 );

}
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
        if(currentPiece == juego->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);

            return;
        }

        //se seleeciona pieza
        if(juego->pieceToMove){

            //si esta en el mismo equipo no se puede mover si ya ha movido
            if(this->getChessPieceColor() == juego->pieceToMove->getSide()){
                return;}

            //eliminando si esta muerta esta pieza
            QList <Cell *> movLoc = juego->pieceToMove->moveLocation();

            //chekea que esta en una de las celdas donde si se puede mover
            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;
                    juego->pieceToMove->control.destiny=this->name;
                     qDebug()<<juego->pieceToMove->control.destiny;
                }
            }
            // si no retorna
            if(check == 0)
                return;
            //cambia el color a normal
             juego->pieceToMove->recolor();
             //hace el primer movimiento falta para peones
             juego->pieceToMove->firstMove = false;
             //realiza la accion de comer una fiiicha

            if(this->getHasChessPiece()){
                this->currentPiece->setMoved(false);
                this->currentPiece->setCurrentCell(NULL);
                juego->placeInDeadPlace(this->currentPiece);
            }
            //resetando la region previa
            juego->pieceToMove->getCurrentCell()->setHasChessPiece(false);
            juego->pieceToMove->getCurrentCell()->currentPiece = NULL;
            juego->pieceToMove->getCurrentCell()->resetOriginalColor();
            placePiece(juego->pieceToMove);

            juego->pieceToMove = NULL;
            //cambiando el turno
            juego->changeTurn();
            checkForCheck();
        }
        else if(this->getHasChessPiece())
        {
            this->currentPiece->mousePressEvent(event);
        }
}

//cambia el color por uno que se le indique
void Cell::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

//se encarga de poner las piezas en un lugar deseado del pixman
void Cell::placePiece(Piece *piece)
{
    piece->setPos(x()+40- piece->pixmap().width()/2  ,y()+40-piece->pixmap().width()/2);
    piece->setCurrentCell(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;
}

//resetea el color al original
void Cell::resetOriginalColor()
{
    setColor(originalColor);
}
//cambia el color originar
void Cell::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

//returna si es que tiene o no una pieza
bool Cell::getHasChessPiece()
{
    return hasChessPiece;
}

//obtiene el valor del lugar de la pieza
void Cell::setHasChessPiece(bool value, Piece *piece)
{
    hasChessPiece = value;

    if(value){
        setChessPieceColor(piece->getSide());
    }else
        setChessPieceColor("NONE");
}

//se encarga de ir checkeando continuamente si hay algun jake mate
void Cell::checkForCheck()
{
    int c = 0;
    int contrey=0;
        QList <Piece *> pList = juego->piecesInGame;
        for(size_t i = 0,n=pList.size(); i < n; i++ ) {

            King * p = dynamic_cast<King *> (pList[i]);
            if(p){
                contrey++;
                continue;
            }
            pList[i]->move();
            pList[i]->recolor();
            QList <Cell *> bList = pList[i]->moveLocation();
            for(size_t j = 0,n = bList.size(); j < n; j ++) {
                King * p = dynamic_cast<King *> (bList[j]->currentPiece);
                if(p) {
                    if(p->getSide() == pList[i]->getSide())
                        continue;
                    bList[j]->setColor(Qt::blue);
                    pList[i]->getCurrentCell()->setColor(Qt::darkRed);
                    if(!juego->check->isVisible())
                        juego->check->setVisible(true);
                    else{
                        bList[j]->resetOriginalColor();
                        pList[i]->getCurrentCell()->resetOriginalColor();

                        if(QString::compare(juego->getTurn(),"WHITE")){

                            juego->check->setPlainText("Black Won");
                            juego->check->setVisible(true);
                            QMessageBox Msgbox;
                            Msgbox.setWindowTitle("Chess Winneer!!");
                            Msgbox.setText("Black won!!");
                            Msgbox.exec();
                        }
                        else if(QString::compare(juego->getTurn(),"BLACK")){
                            juego->check->setPlainText("White Won");
                            juego->check->setVisible(true);
                            QMessageBox Msgbox;
                            Msgbox.setWindowTitle("Chess Winneer!!");
                            Msgbox.setText("White won!!");
                            Msgbox.exec();
                        }
                        juego->gameOver();

                    }
                    c++;

                }
            }
        }
        if(contrey==1){
            if(QString::compare(juego->getTurn(),"WHITE")){
                juego->check->setVisible(true);
                juego->check->setPlainText("¡¡Negro Ganó!!");
                QMessageBox Msgbox;
                Msgbox.setWindowTitle("¡¡Ganador de Ajedrez!!");
                Msgbox.setText("¡¡Negro Ganó!!");
                Msgbox.exec();
            }
            else if(QString::compare(juego->getTurn(),"BLACK")){
                juego->check->setVisible(true);
                juego->check->setPlainText("¡¡Blanco Ganó!!");
                QMessageBox Msgbox;
                Msgbox.setWindowTitle("¡¡Ganador de Ajedrez!!");
                Msgbox.setText("¡¡Blanco Ganó!!");
                Msgbox.exec();
            }
            juego->gameOver();
        }
        if(!c){
            juego->check->setVisible(false);
            for(size_t i = 0,n=pList.size(); i < n; i++ )
                pList[i]->getCurrentCell()->resetOriginalColor();
              }
        }

//obtener el color de la pieza
QString Cell::getChessPieceColor()
{
    return chessPieceColor;
}

//cambio de el color de la pieza
void Cell::setChessPieceColor(QString value)
{
    chessPieceColor = value;
}

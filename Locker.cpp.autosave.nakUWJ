#include "Locker.h"
#include "juego.h"
#include <memory>
#include <QDebug>
#include "king.h"
#include <QLabel>
#include <QMessageBox>

extern Juego *juego;
ChessCell::ChessCell(QString text,QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //dibujar la celda
    setRect(0,0,100,100);
    QPainter *painter=new QPainter();
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");
    currentPiece = NULL;
}

ChessCell::~ChessCell()
{
    delete this;
}
void ChessCell::setText(QString text){
    texto = new QGraphicsTextItem(text, this);
    int xPos = rect().width()/2 - texto->boundingRect().width()/2;
    int yPos = rect().height()/2 - texto->boundingRect().height()/2;
    texto->setZValue(0.5);
    texto->setDefaultTextColor(Qt::white);
    texto->setFont(QFont("",20));
    texto->setPos(xPos-10,20 );
    texto->setDefaultTextColor(Qt::white);
}
void ChessCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
            QList <ChessCell *> movLoc = juego->pieceToMove->moveLocation();

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
void ChessCell::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

//se encarga de poner las piezas en un lugar deseado del pixman
void ChessCell::placePiece(Piece *piece)
{
    piece->setPos(x()+40- piece->pixmap().width()/2  ,y()+40-piece->pixmap().width()/2);
    piece->setCurrentCell(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;
}

//resetea el color al original
void ChessCell::resetOriginalColor()
{
    setColor(originalColor);
}


//cambia el color originar
void ChessCell::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

//returna si es que tiene o no una pieza
bool ChessCell::getHasChessPiece()
{
    return hasChessPiece;
}

//obtiene el valor del lugar de la pieza
void ChessCell::setHasChessPiece(bool value, Piece *piece)
{
    hasChessPiece = value;

    if(value){
        setChessPieceColor(piece->getSide());
    }else
        setChessPieceColor("NONE");
}

//se encarga de checkear continuamente si hay algun jake mate
void ChessCell::checkForCheck()
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
            QList <ChessCell *> bList = pList[i]->moveLocation();
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
                juego->check->setPlainText("Black Won");
                QMessageBox Msgbox;
                Msgbox.setWindowTitle("Chess Winneer!!");
                Msgbox.setText("Black won!!");
                Msgbox.exec();
            }
            else if(QString::compare(juego->getTurn(),"BLACK")){
                juego->check->setVisible(true);
                juego->check->setPlainText("White Won");
                QMessageBox Msgbox;
                Msgbox.setWindowTitle("Chess Winneer!!");
                Msgbox.setText("White won!!");
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

//obtener el color de la pieza que se contiene
QString ChessCell::getChessPieceColor()
{
    return chessPieceColor;
}

//cambiazo el color de la pieza que se contiene
void ChessCell::setChessPieceColor(QString value)
{
    chessPieceColor = value;
}

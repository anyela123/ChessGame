#include "juego.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
#include <QColor>
#include <iostream>
#include <QMessageBox>


Juego::Juego(QWidget *parent ):QGraphicsView(parent)
{
    //construyendo la escena
    chessScene = new QGraphicsScene();
    chessSceneWhite = new QGraphicsScene();
    //layout

    chessScene->setSceneRect(0,0,1566,900);
    QMessageBox msbx;
    //costruyendo la vista
    setMinimumSize(1366,700);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(chessScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(200,162,173));
    setBackgroundBrush(brush);
    pieceToMove = NULL;


    Turn= new  QGraphicsRectItem();
    Turn->setRect(0,0,300,40);
    Turn->setPos(width()/2,0);
    QBrush brush2;
    brush2.setStyle(Qt::SolidPattern);
    brush2.setColor(QColor(255,255,255));
    Turn->setBrush(brush2);
    // muestra el check (jaque) como aviso
    check = new QGraphicsTextItem();
    check->setPos(65,chessScene->height()/2);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("",20));
    check->setPlainText("CHECK, THERE IS A \n POSSIBLE \n CHECKMATE!!");
    check->setVisible(false);
    setTurn("WHITE");

     newItem=new QTableWidgetItem();
                 // para que los elementos no sean editables
     newItem->setFlags(newItem->flags() & (~Qt::ItemIsEditable));
     newItem->setTextColor(Qt::blue); // color de los items

     tableWidget = new QTableWidget(this);
     tableWidget->setRowCount(50);
     tableWidget->setColumnCount(4);
     rowCount = tableWidget->rowCount();
     colCount = tableWidget->columnCount();


}

//muestra e inicializa el board
void Juego::showBoard()
{
    chess = new Board();
    chess->initializeBoard(width()/2-250,50);


}

//dibuja el cuadro que contendra a las piezas blancas muertas
void Juego::displayDeadWhite()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = whiteDead.size(); i<n; i++) {
            if(j == 4){
                k++;
                j = 0;
            }
            whiteDead[i]->setPos(40+SHIFT*j++,65+SHIFT*2*k);
    }

}

//dibuja el cuadro que contendra a las piezas negras muertas
void Juego::displayDeadBlack()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = blackDead.size(); i<n; i++) {
        if(j == 4){
            k++;
            j = 0;
        }
        blackDead[i]->setPos(40+SHIFT*j++,500+SHIFT*2*k);

    }
}

//verifica si se ha acabado el juego
void Juego::placeInDeadPlace(Piece *piece)
{
    if(piece->getSide() == "WHITE") {
        whiteDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        if(g){

            check->setPlainText("Black Won");
            QMessageBox Msgbox;
            Msgbox.setWindowTitle("Chess Winneer!!");
            Msgbox.setText("Black won!!");
            Msgbox.exec();
            gameOver();
        }
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        if(g){
            check->setPlainText("White Won");
            QMessageBox Msgbox;
            Msgbox.setWindowTitle("Chess Winneer!!");
            Msgbox.setText("White won!!");
            Msgbox.exec();

            gameOver();
        }
        displayDeadBlack();
    }
    piecesInGame.removeAll(piece);
}

//agrega un item a la escena
void Juego::aggregateToScene(QGraphicsItem *item)
{
    chessScene->addItem(item);
}

//elimina un dterminado item de la escena
void Juego::deleteToScene(QGraphicsItem *item)
{
    chessScene->removeItem(item);

}

//devuelve el turno actual
QString Juego::getTurn()
{
    return turn;
}

//cambiamos el turno
void Juego::setTurn(QString value)
{
    turn = value;
}

//para cambiar de turno
void Juego::changeTurn()
{
    if(getTurn() =="WHITE"){
        setTurn("BLACK");
        QBrush brush2;
        brush2.setStyle(Qt::SolidPattern);
        brush2.setColor(QColor(0,0,0));
        Turn->setBrush(brush2);
    }
    else{
        setTurn("WHITE");
        QBrush brush2;
        brush2.setStyle(Qt::SolidPattern);
        brush2.setColor(QColor(255,255,255));
        Turn->setBrush(brush2);
    }
    //frameTurn->setPlainText("Turn : " + getTurn());
}

//para empezar el juego, agregamos lo necesario
void Juego::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
            deleteToScene(listG[i]);

    //aggregateToScene(frameTurn);
    aggregateToScene(Turn);
    //lugar para las piezas blancas muertas
    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(65,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::white);
    whitePiece->setFont(QFont("",14));
    whitePiece->setPlainText("PIEZAS BLANCAS CAPTURADAS");
    aggregateToScene(whitePiece);

    //lugar para las piezas blancas muertas
    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();
    blackPiece->setPos(65,chessScene->height()/2);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::white);
    blackPiece->setFont(QFont("",14));
    blackPiece->setPlainText("PIEZAS NEGRAS CAPTURADAS");
    aggregateToScene(blackPiece);
    aggregateToScene(check);
    chess->addPieces();    


}

//dibujamos el frame que contendra los muertos
void Juego::displayDeadsFrame(int x, int y)
{
    deadHolder = new QGraphicsRectItem(x,y,30,90);
    QBrush brush;
    brush.setColor(QColor(234,215,15));
    brush.setStyle(Qt::SolidPattern);
    deadHolder->setBrush(brush);
    aggregateToScene(deadHolder);
}

//para dibujar el menu
void Juego::displayMainMenu()
{
    //boton para jugar
    Button * jugar = new Button("Comenzar");
    uint16_t jXPos = 70;
    uint16_t jYPos = 350;
    jugar->setPos(jXPos,jYPos);
    connect(jugar,SIGNAL(clicked()) , this , SLOT(start()));
    aggregateToScene(jugar);
    listG.append(jugar);

     showBoard();

}

//se ejecuta cuando alguno gane, reseteando el juego
void Juego::gameOver(){
    check->setPlainText("CHECK, THERE IS A \n POSSIBLE \n CHECKMATE!!");
    check->setVisible(false);
    setTurn("WHITE");
    piecesInGame.clear();
    whiteDead.clear();
    blackDead.clear();
    chess->reset();

}

//eliminamos absolutamente todo lo que este en la escena
void Juego::removeAll(){
    QList<QGraphicsItem*> itemsList = chessScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          deleteToScene(itemsList[i]);
    }
}

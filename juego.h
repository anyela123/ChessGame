#ifndef CORE_H
#define CORE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <board.h>
#include "piece.h"
#include <QGridLayout>
#include <QTableWidget>
class Juego:public QGraphicsView
{
    Q_OBJECT
public:
    //Constructor
    Juego(QWidget *parent = 0);

    void displayDeadsFrame( int x, int y);
    void showBoard();
    void showDeadWhites();
    void showDeadBlack();
    void placeInDeadPlace(Piece *piece);

    //metodos para manejar la escena
    void aggregateToScene(QGraphicsItem *item);      //agrega a la escena
    void deleteToScene(QGraphicsItem *item); //elminina de la escena

    //pieza a mover
    Piece *pieceToMove;

    //conocer el turno
    QString getTurn() ;
    //setea de turno
    void setTurn( QString value);
    //cambia de turno
    void changeTurn();


    //coleccion de celdas
    Cell *collection[10][10];
    QGraphicsTextItem *check;
    //verifica las piezas vivas
    QList <Piece *> piecesInGame;
    void displayDeadWhite();
    void displayDeadBlack();

    //dibuja el menu principal
    void displayMainMenu();
    //to implement, cuando el juego acabe
    void gameOver();
    //elimina todo
    void removeAll();
     QTableWidgetItem *newItem;
     QTableWidget *tableWidget;
     int rowCount;
     int colCount;

public slots:
    void start();
private:

    QGraphicsScene *chessScene;
    QGraphicsScene *chessSceneWhite;
    QTimer *timer;
    QList <Piece *> whiteDead;
    QList <Piece *> blackDead;
    QGraphicsRectItem * deadHolder;
    QString turn;
    Board *chess;
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * frameTurn;
    QGraphicsRectItem * Turn;
};

#endif // CORE_H

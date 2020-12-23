#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "piece.h"
class Board
{
public:
    Board();

    //dibuja los cuadros
    void initializeBoard(int x, int y);

    //agrega las piezas al tablero
    void addPieces();

    //incluye las piezas blancas
    void initializeWhite();

    //incluye las piezas negras
    void initializeBlack();

    void reset();
private:
    QList <Piece *> whitePieces;
    QList <Piece *> blackPieces;
    QString names[8][8]={{"a8","b8","c8","d8","e8","f8","g8","h8"},
                            {"a7","b7","c7","d7","e7","f7","g7","h7"},
                            {"a6","b6","c6","d6","e6","f6","g6","h6"},
                            {"a5","b5","c5","d5","e5","f5","g5","h5"},
                            {"a4","b4","c4","d4","e4","f4","g4","h4"},
                            {"a3","b3","c3","d3","e3","f3","g3","h3"},
                            {"a2","b2","c2","d2","e2","f2","g2","h2"},
                            {"a1","b1","c1","d1","e1","f1","g1","h1"}};
    enum { NumLocker = 10 };
     QString letters[8]={"a","b","c","d","e","f","g","h"};
};

#endif // CHESSBOARD_H

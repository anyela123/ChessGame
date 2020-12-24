#include "board.h"
#include "Cell.h"
#include "juego.h"
#include "queen.h"
#include "tower.h"
#include "pawn.h"
#include "king.h"
#include "horse.h"
#include "bishop.h"
#include <QColor>
#include <QRect>
#include <QDebug>

extern Juego *juego;
Board::Board()
{
    initializeBlack();  //inicializar las fichas negras
    initializeWhite();  //inicializar las fichas blancas
}

//dibujando los cuadros
void Board::initializeBoard(int x,int y)
{
    uint16_t sizeCell = 70;// tamaño celda
    int k=0,l=0;
    int m=8,n=8;
    for(uint16_t i = 0; i < NumLocker; i++) {
        for(uint16_t j = 0; j < NumLocker; j++)
        {   Cell *cell = new Cell(""); //celda nueva
            juego->collection[i][j] = cell;
            cell->rowLoc = i;
            cell->colLoc = j;
            cell->setPos(x+sizeCell*j,y+sizeCell*i); // va aumentado posicion  a ubicar
            if(i==0 || i==9 || j==0 || j==9){
                cell->setOriginalColor(QColor(255, 255, 255));
                if(i==0 && j==0|| i==9 && j==9 || i==9 && j==0 || i==0 && j==9)
                    cell->setText("");
                else if(i==0 || i==9 ){
                       if(i==9){
                     cell->setText(letters[k]);
                     k++;}
                       else{
                           cell->setText(letters[l]);
                           l++;
                       }
                }
                else if(j==0 || j==9){
                    if(j==9){
                    cell->setText(QString::number(m));
                    m--;}
                    else{
                     cell->setText(QString::number(n));
                      n--;
                    }
                }

            }
            else{
                if(i<9 & j<9)
                cell->name=names[i-1][j-1];
                //qDebug()<<cell->name<<cell->rowLoc<<"-"<<cell->colLoc;

            if((i+j)%2==0)
                cell->setOriginalColor(QColor(158, 110, 39)); //marron fuerte
            else
                cell->setOriginalColor(QColor(245, 202, 138));
            }//marron claro
                juego->aggregateToScene(cell);
        }
    }

}

//agregando las piezas en las listas
void Board::addPieces() {
    for(uint16_t i = 1; i < 9; i++) {
        for(uint16_t j = 1; j < 9; j++)
        {

            Cell *cell =juego->collection[i][j];
            if(i < 3 ) {
                static uint16_t k;
                cell->placePiece(blackPieces[k]);
                juego->piecesInGame.append(blackPieces[k]);
                juego->aggregateToScene(blackPieces[k++]);
            }
            if(i > 6 ) {
                static uint16_t h;
                cell->placePiece(whitePieces[h]);
                juego->piecesInGame.append(whitePieces[h]);
                juego->aggregateToScene(whitePieces[h++]);
            }

        }
    }
}

//inicializar las fichas blancas
void Board::initializeWhite()
{
    Piece *pieceToAdd;
    for(int i = 1; i < 9; i++) {
        pieceToAdd = new Pawn("WHITE");
        whitePieces.append(pieceToAdd);
    }
    pieceToAdd = new Tower("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Horse("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Bishop("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Queen("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new King("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Bishop("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Horse("WHITE");
    whitePieces.append(pieceToAdd);
    pieceToAdd = new Tower("WHITE");
    whitePieces.append(pieceToAdd);

}

//inicializando las piezas negras
void Board::initializeBlack()
{
    Piece *pieceToAdd;
    pieceToAdd = new Tower("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Horse("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Bishop("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Queen("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new King("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Bishop("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Horse("BLACK");
    blackPieces.append(pieceToAdd);
    pieceToAdd = new Tower("BLACK");
    blackPieces.append(pieceToAdd);
    for(int i = 0; i < 8; i++) {
        pieceToAdd = new Pawn("BLACK");
        blackPieces.append(pieceToAdd);
    }
}

//resetea el board una vez haya ganado uno de los jugadores
void Board::reset() {
    initializeWhite();
    initializeBlack();

    int k = 0; int h = 0;
        for(int i = 1; i < 9; i++) {
            for(int j = 1; j < 9; j++)
            {

                Cell *box =juego->collection[i][j];
                box->setHasChessPiece(false);
                box->setChessPieceColor("NONE");
                box->currentPiece = NULL;
                if(i < 3 ) {

                    box->placePiece(blackPieces[k]);
                    blackPieces[k]->setMoved(true);
                    blackPieces[k]->firstMove = true;
                    juego->piecesInGame.append(blackPieces[k++]);

                }
                if(i > 6  ) {

                    box->placePiece(whitePieces[h]);
                    whitePieces[h]->setMoved(true);
                    whitePieces[h]->firstMove = true;
                    juego->piecesInGame.append(whitePieces[h++]);

                }

            }
        }
}

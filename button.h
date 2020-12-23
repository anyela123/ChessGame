#ifndef BUTTON_H
#define BUTTON_H
#include <memory>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

class Button: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    //constructor explicito
    Button(QString nombre, QGraphicsItem * parent = NULL);

    //eventos con el boton
    void mousePressEvent(QGraphicsSceneMouseEvent *evento);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *evento);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *evento);
signals:
    void clicked();
private:
    QGraphicsTextItem *texto;
};

#endif // BUTTON_H

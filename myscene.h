#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>

class ResizeableItem : public QGraphicsItem
{

};


class ResizeablePixmap : public ResizeableItem, public QGraphicsPixmapItem
{

public:
    ResizeablePixmap(QPixmap pix);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class myscene : public QGraphicsScene
{
Q_OBJECT
public:
    myscene();
    QGraphicsPixmapItem * m_background;
    QPushButton * m_testButton;
public slots:
    void testSlot();
};

#endif // MYSCENE_H

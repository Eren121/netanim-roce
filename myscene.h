#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>




void QDEBUG(QPointF p, QString prefix = "");
void QDEBUG(QString str);

class ResizeablePixmap : public QGraphicsPixmapItem
{

public:
    ResizeablePixmap(QPixmap pix);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    bool m_mousePressed;

};

class myscene : public QGraphicsScene
{
Q_OBJECT
public:
    myscene();
    ResizeablePixmap * m_background;
    QPushButton * m_testButton;
public slots:
    void testSlot();
};

#endif // MYSCENE_H

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
    typedef enum {
        RESIZE_RIGHT,
        RESIZE_LEFT,
        RESIZE_TOP,
        RESIZE_BOTTOM,
        RESIZE_NOTRESIZING
    } ResizeDirection_t;
    ResizeablePixmap(QPixmap pix);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    bool m_mousePressed;
    ResizeDirection_t m_currentResizeDirection;
    ResizeDirection_t m_lastResizeDirection;
    bool m_resizing;
    qreal m_lastResizingX;
    qreal m_lastResizingY;

};

class myscene : public QGraphicsScene
{
Q_OBJECT
public:
    myscene();
    ResizeablePixmap * m_background;
    ResizeablePixmap * m_pItem;
    QPushButton * m_testButton;
    void addPix();
public slots:
    void testSlot();
};

#endif // MYSCENE_H

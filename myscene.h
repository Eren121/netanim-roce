#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>




void QDEBUG(QPointF p, QString prefix = "");
void QDEBUG(QString str);


#define PIXMAP_RESIZING_BORDER 3
#define PIXMAP_WIDTH_MIN 20

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
    qreal getItemWidth();
    qreal getItemHeight();
    qreal getBorderWidth();

private:
    bool m_mousePressed;
    ResizeDirection_t m_currentResizeDirection;
    ResizeDirection_t m_lastResizeDirection;
    bool m_resizing;
    bool isResizing();
    void setResizingDirection(ResizeDirection_t direction);

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
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void testSlot();
};

#endif // MYSCENE_H

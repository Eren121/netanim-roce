#include "myscene.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneHoverEvent>


void QDEBUG(QPointF p, QString prefix)
{
    QString str = "X:" + QString::number(p.x()) + " Y:" + QString::number(p.y());
    QDEBUG(prefix + ":" + str);
}

void QDEBUG(QString str)
{
    str = "QD:" + str;
    qDebug(str.toAscii());
}


ResizeablePixmap::ResizeablePixmap(QPixmap pix): QGraphicsPixmapItem(pix), m_mousePressed(false)
{
    setAcceptsHoverEvents(true);

}

void ResizeablePixmap::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QCursor c(Qt::OpenHandCursor);
    setCursor(c);
    qreal borderWidth = 3;
    qreal bottomRightX = boundingRect().bottomRight().x();
    qreal bottomRightXLow = bottomRightX - borderWidth;

    qreal bottomRightY = boundingRect().bottomRight().y();
    qreal bottomRightYLow = bottomRightY - borderWidth;

    qreal eventPosX = event->pos().x();
    qreal eventPosY = event->pos().y();
    if (((eventPosX >= bottomRightXLow) && (eventPosX <= bottomRightX)) ||
            (eventPosX <= borderWidth))
    {
        QCursor c(Qt::SizeHorCursor);
        setCursor(c);
    }
    else if (((eventPosY >= bottomRightYLow) && (eventPosY <= bottomRightY)) ||
         (eventPosY <= borderWidth))
    {
        QCursor c(Qt::SizeVerCursor);
        setCursor(c);

    }
    return QGraphicsPixmapItem::hoverMoveEvent(event);
}

QRectF ResizeablePixmap::boundingRect() const
{
    return QGraphicsPixmapItem::boundingRect();
}

void ResizeablePixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    return QGraphicsPixmapItem::paint(painter, option, widget);

}

myscene::myscene()
{
    m_testButton = new QPushButton("Test");
    connect(m_testButton, SIGNAL(clicked()), this, SLOT(testSlot()));
    addWidget(m_testButton);
    QPixmap pix("/Users/john/ns-3/newcanvas1/ns3logo2.png","png");

    m_background = new ResizeablePixmap(pix);
    m_background->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    m_background->setZValue(-100);
    addItem(m_background);

}


void myscene::testSlot()
{
    static int i = 0;
    addEllipse(i++, 15, 4, 4);
    QPixmap pix("/Users/john/ns-3/newcanvas1/ns3logo2.png","png");
    QSize s;
    s.setHeight(5);
    s.setWidth(5);
    pix.scaled(s);
    ResizeablePixmap * pItem = new ResizeablePixmap(pix);
    addItem(pItem);
    pItem->setZValue(0);
    pItem->scale(.3, .3);
    pItem->setPos(15, 15);

    qDebug("Hi");
}

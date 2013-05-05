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


ResizeablePixmap::ResizeablePixmap(QPixmap pix):
    QGraphicsPixmapItem(pix),
    m_mousePressed(false),
    m_currentResizeDirection(RESIZE_NOTRESIZING),
    m_lastResizeDirection(RESIZE_NOTRESIZING),
    m_resizing(false)
{
    setAcceptsHoverEvents(true);
}

void ResizeablePixmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("Mouse pressed");
    m_mousePressed = true;
    QGraphicsPixmapItem::mousePressEvent(event);
}

void ResizeablePixmap::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal bottomRightX = boundingRect().bottomRight().x();

    qreal bottomRightY = boundingRect().bottomRight().y();

    qreal eventPosX = event->pos().x();
    qreal eventPosY = event->pos().y();
    QGraphicsPixmapItem::mouseMoveEvent(event);
    if ((m_currentResizeDirection != RESIZE_NOTRESIZING) && (m_currentResizeDirection == m_lastResizeDirection) && (m_mousePressed))
    {
        //DoResize
        QTransform transform;
        transform.scale(eventPosX/bottomRightX, 1);
        setTransform(transform);
        qDebug("Transforming");

    }
}


void ResizeablePixmap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("Mouse released");
    m_mousePressed = false;
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void ResizeablePixmap::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

    qreal borderWidth = 3;
    qreal bottomRightX = boundingRect().bottomRight().x();
    qreal bottomRightXLow = bottomRightX - borderWidth;

    qreal bottomRightY = boundingRect().bottomRight().y();
    qreal bottomRightYLow = bottomRightY - borderWidth;

    qreal eventPosX = event->pos().x();
    qreal eventPosY = event->pos().y();
    if (((eventPosX >= bottomRightXLow) && (eventPosX <= bottomRightX)))
    {
        setFlags(QGraphicsItem::ItemIsSelectable);
        QCursor c(Qt::SizeHorCursor);
        setCursor(c);
        m_currentResizeDirection = RESIZE_RIGHT;
    }
    else if (eventPosX <= borderWidth)
    {
        setFlags(QGraphicsItem::ItemIsSelectable);
        QCursor c(Qt::SizeHorCursor);
        setCursor(c);
        m_currentResizeDirection = RESIZE_LEFT;
    }
    else if (((eventPosY >= bottomRightYLow) && (eventPosY <= bottomRightY)))
    {
        setFlags(QGraphicsItem::ItemIsSelectable);
        QCursor c(Qt::SizeVerCursor);
        setCursor(c);
        m_currentResizeDirection = RESIZE_BOTTOM;
    }
    else if (eventPosY <= borderWidth)
    {
        setFlags(QGraphicsItem::ItemIsSelectable);
        QCursor c(Qt::SizeVerCursor);
        setCursor(c);
        m_currentResizeDirection = RESIZE_TOP;
    }
    else
    {
        setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
        QCursor c(Qt::OpenHandCursor);
        setCursor(c);
        m_currentResizeDirection = RESIZE_NOTRESIZING;
    }
    QGraphicsPixmapItem::hoverMoveEvent(event);
    if ((m_lastResizeDirection == RESIZE_NOTRESIZING) && (m_lastResizeDirection != m_currentResizeDirection))
    {
        m_lastResizingX = eventPosX;
        m_lastResizingY = eventPosY;
    }
    QDEBUG("Current Resize Direction:" + QString::number(m_currentResizeDirection) + " Last Resize:" + QString::number(m_lastResizeDirection));

    m_lastResizeDirection = m_currentResizeDirection;
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

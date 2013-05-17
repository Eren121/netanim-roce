#include "log.h"
#include "logqt.h"
#include "myscene.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneHoverEvent>

using namespace ns3;
NS_LOG_COMPONENT_DEFINE("MyScene");


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
    NS_LOG_FUNCTION(m_mousePressed);
    setAcceptsHoverEvents(true);
}

void ResizeablePixmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("Mouse pressed");
    m_mousePressed = true;
    QGraphicsPixmapItem::mousePressEvent(event);
}

bool ResizeablePixmap::isResizing()
{
    return (m_currentResizeDirection == m_lastResizeDirection);
}
void ResizeablePixmap::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //NS_LOG_FUNCTION("Event Pos: " << event->pos() << " SB Rect:" << sceneBoundingRect());
    QGraphicsPixmapItem::mouseMoveEvent(event);
    NS_LOG_DEBUG("POS:" << pos() << " EventPos:" << event->pos() << sceneBoundingRect().topLeft());
    if (!m_mousePressed || !isResizing())
        return;
    qreal eventPosX = event->pos().x();
    if ((m_currentResizeDirection == RESIZE_RIGHT))
    {
        qreal xScale = eventPosX/getItemWidth();
        scale(xScale, 1);
    }
    if ((m_currentResizeDirection == RESIZE_LEFT))
    {
        qreal xScale = (getItemWidth() - eventPosX)/getItemWidth();
        qreal savedY = pos().y();
        scale(xScale, 1);
        setPos(QPointF(mapToScene(event->pos())).x(), savedY );
    }




}


qreal ResizeablePixmap::getItemWidth()
{
    //NS_LOG_FUNCTION_NOARGS();
    QPointF sceneLeft = sceneBoundingRect().topLeft();
    QPointF sceneRight = sceneBoundingRect().topRight();
    QPointF itemMapLeft = mapFromScene(sceneLeft);
    QPointF itemMapRight = mapFromScene(sceneRight);
    qreal w = itemMapRight.x() - itemMapLeft.x();
    NS_LOG_DEBUG ("ItemWidth:" << w);
    return w;

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

    qreal eventPosX = (event->pos()).x();
    qreal eventPosY = (event->pos()).y();
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
    //QDEBUG("Current Resize Direction:" + QString::number(m_currentResizeDirection) + " Last Resize:" + QString::number(m_lastResizeDirection));

    m_lastResizeDirection = m_currentResizeDirection;
}

QRectF ResizeablePixmap::boundingRect() const
{
    return QGraphicsPixmapItem::boundingRect();
}

void ResizeablePixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //NS_LOG_DEBUG(sceneBoundingRect());
    return QGraphicsPixmapItem::paint(painter, option, widget);

}

myscene::myscene():QGraphicsScene(0, 0, 1000, 1000)
{
    m_testButton = new QPushButton("Test");
    connect(m_testButton, SIGNAL(clicked()), this, SLOT(testSlot()));
    addWidget(m_testButton);
    QPixmap pix(":/new/prefix1/ns3logo2.png","png");

    m_background = new ResizeablePixmap(pix);
    m_background->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    m_background->setZValue(-100);
    //addItem(m_background);
    //testSlot();
    addPix();
}

void myscene::testSlot()
{
    NS_LOG_DEBUG("Before:" << m_pItem->sceneBoundingRect() << " Pos:" << m_pItem->pos());
    m_pItem->scale(1.1, 1);
    NS_LOG_DEBUG("After:" << m_pItem->sceneBoundingRect() << " Pos:" << m_pItem->pos());

}

void myscene::addPix()
{
    static int i = 0;
    addEllipse(i++, 15, 4, 4);
    QPixmap pix(":/new/prefix1/ns3logo2.png","png");
    QSize s;
    s.setHeight(5);
    s.setWidth(5);
    pix.scaled(s);
    m_pItem = new ResizeablePixmap(pix);
    addItem(m_pItem);
    m_pItem->setZValue(0);
    m_pItem->scale(.3, .3);
    m_pItem->setPos(355, 355);

    qDebug("Hi");
}

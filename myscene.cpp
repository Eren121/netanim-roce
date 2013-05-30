#include "log.h"
#include "logqt.h"
#include "myscene.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>

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
    qreal eventPosY = event->pos().y();
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
    if ((m_currentResizeDirection == RESIZE_TOP))
    {
        qreal yScale = (getItemHeight()- eventPosY)/getItemHeight();
        qreal savedX = pos().x();
        scale(1, yScale);
        setPos(savedX, QPointF(mapToScene(event->pos())).y());
    }
    if ((m_currentResizeDirection == RESIZE_BOTTOM))
    {
        qreal yScale = eventPosY/getItemHeight();
        scale(1, yScale);
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

qreal ResizeablePixmap::getItemHeight()
{
    QPointF sceneTop = sceneBoundingRect().topLeft();
    QPointF sceneBottom = sceneBoundingRect().bottomLeft();
    QPointF itemMapTop = mapFromScene(sceneTop);
    QPointF itemMapBottom = mapFromScene(sceneBottom);
    qreal h = itemMapBottom.y() - itemMapTop.y();
    NS_LOG_DEBUG ("ItemHeight:" << h);
    return h;
}

void ResizeablePixmap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("Mouse released");
    m_mousePressed = false;
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

void ResizeablePixmap::setResizingDirection(ResizeDirection_t direction)
{
    QCursor c;
    switch (direction)
    {

        case RESIZE_BOTTOM:
        case RESIZE_TOP:
            c.setShape(Qt::SizeVerCursor);
            setFlags(QGraphicsItem::ItemIsSelectable);
            break;
        case RESIZE_LEFT:
        case RESIZE_RIGHT:
            c.setShape(Qt::SizeHorCursor);
            setFlags(QGraphicsItem::ItemIsSelectable);
            break;
        case RESIZE_NOTRESIZING:
            c.setShape(Qt::OpenHandCursor);
            setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);


    }
    setCursor(c);
    m_currentResizeDirection = direction;
}

qreal ResizeablePixmap::getBorderWidth()
{

    QGraphicsView * view = scene()->views().last();
    QPointF scenePos1 = view->mapToScene(QPointF(0, 0).toPoint());
    QPointF scenePos2 = view->mapToScene(QPointF(5, 0).toPoint());
    NS_LOG_DEBUG("Mapped scenePos:" << scenePos1 << " SceneRect:" << view->sceneRect());
    return qAbs(scenePos2.x() - scenePos1.x());




}

void ResizeablePixmap::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    //prepareGeometryChange();update();

    //QPointF itemBorderPoint = mapFromScene(QPointF(PIXMAP_RESIZING_BORDER), 0);
    //QPointF itemTopLeft =
    //NS_LOG_DEBUG("Item Rect:" << boundingRect() << " Event Pos:" << event->pos());
    NS_LOG_DEBUG("transform: " << transform());
    //NS_LOG_DEBUG("Item Transform:" << itemTransform());
    //NS_LOG_DEBUG("SCENE Transform:" << scene()->)
    //NS_LOG_DEBUG("SCENE Transform:" << );
    //NS_LOG_DEBUG("Scene Rect:" << sceneBoundingRect());
    qreal borderWidth = getBorderWidth() ;//* transform().m11();// 5* transform().m11() ;// * transform().m11() / sceneTransform().m11(); // sceneBoundingRect().width()/10;
    NS_LOG_DEBUG("BorderWidth:" << borderWidth);
    qreal bottomRightX = sceneBoundingRect().bottomRight().x();
    qreal bottomRightXLow = bottomRightX - borderWidth;
    qreal bottomLeftX = sceneBoundingRect().bottomLeft().x();

    qreal bottomRightY = sceneBoundingRect().bottomRight().y();
    qreal bottomRightYLow = bottomRightY - borderWidth;
    qreal topLeftY = sceneBoundingRect().topLeft().y();

    NS_LOG_DEBUG("Hover ScenePos:" << mapToScene(event->pos()) << " LeftX:" << bottomLeftX);
    qreal eventPosX = (mapToScene(event->pos())).x();
    qreal eventPosY = (mapToScene(event->pos())).y();
    if (((eventPosX >= bottomRightXLow) && (eventPosX <= bottomRightX)))
    {
        setResizingDirection(RESIZE_RIGHT);
    }
    else if (eventPosX <= (bottomLeftX+borderWidth))
    {
        setResizingDirection(RESIZE_LEFT);
    }
    else if (((eventPosY >= bottomRightYLow) && (eventPosY <= bottomRightY)))
    {
        setResizingDirection(RESIZE_BOTTOM);
    }
    else if (eventPosY <= (topLeftY+borderWidth))
    {
        setResizingDirection(RESIZE_TOP);
    }
    else
    {
        setResizingDirection(RESIZE_NOTRESIZING);
    }
    QGraphicsPixmapItem::hoverMoveEvent(event);
    //QDEBUG("Current Resize Direction:" + QString::number(m_currentResizeDirection) + " Last Resize:" + QString::number(m_lastResizeDirection));

    m_lastResizeDirection = m_currentResizeDirection;
}

QRectF ResizeablePixmap::boundingRect() const
{
    //return boundingRegion(transform()).rects().last();
    //return QGraphicsPixmapItem::boundingRect();
    return pixmap().rect();
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
    m_pItem->scale(1.5, 1.5);
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
    m_pItem->scale(1, 1);
    m_pItem->setPos(355, 355);

    qDebug("Hi");
}
void myscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsView * view = views().last();
    NS_LOG_DEBUG("Scene Mouse Move ScenePos:" << event->scenePos());
    //NS_LOG_DEBUG("Scene Mouse Move ScreenPos:" << event->screenPos());

    QPoint viewP = view->mapFromScene(event->scenePos());
    QPoint globalP = view->viewport()->mapToGlobal(viewP);
    //NS_LOG_DEBUG("Scene Mouse Move ViewPos:" << globalP);
    return QGraphicsScene::mouseMoveEvent(event);
}

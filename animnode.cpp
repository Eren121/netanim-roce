#include <QPainter>
#include <QGraphicsScene>
#include "animnode.h"
#include "animatorview.h"
#include "animatorconstants.h"
#include "logqt.h"
#include "log.h"
#include "fatal-error.h"
#include "assert.h"

NS_LOG_COMPONENT_DEFINE("AnimNode");


namespace netanim {

AnimNodeMgr * pAnimNodeMgr = 0;

AnimNode::AnimNode(uint32_t nodeId, qreal x, qreal y, QString nodeDescription):m_nodeDescription(0),
    m_nodeId(nodeId),
    m_x(x),
    m_y(y),
    m_r(255),
    m_g(0),
    m_b(0)
{
    //setVisible(false);
    setZValue(ANIMNODE_ZVALUE);
    if (nodeDescription == "")
    {
        nodeDescription = QString::number(nodeId);
    }
    m_nodeDescription = new QGraphicsTextItem(nodeDescription);
    m_nodeDescription->setFlag(QGraphicsItem::ItemIgnoresTransformations);

}

AnimNode::~AnimNode()
{
}

void
AnimNode::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    m_r = r;
    m_g = g;
    m_b = b;
    ResizeableItem::setColor(r, g, b);
}

void
AnimNode::setWidth(qreal width)
{
    m_width = width;
}

void
AnimNode::setHeight(qreal height)
{
    m_height = height;
}

qreal
AnimNode::getX()
{
    return m_x;
}

qreal
AnimNode::getY()
{
    return m_y;
}

void
AnimNode::setX(qreal x)
{
    m_x = x;
}

void
AnimNode::setY(qreal y)
{
    m_y = y;
}

uint32_t
AnimNode::getNodeId()
{
    return m_nodeId;
}

QGraphicsTextItem *
AnimNode::getDescription()
{
    return m_nodeDescription;
}

QPointF AnimNode::getCenter()
{
    return sceneBoundingRect().center();
}
void AnimNode::setNodeDescription(QString description)
{
    m_nodeDescription->setPlainText(description);
}

void AnimNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ResizeableItem::paint(painter, option, widget);
}


void AnimNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    ResizeableItem::mouseMoveEvent(event);
    if(m_nodeDescription)
    {
        m_nodeDescription->setPos(sceneBoundingRect().bottomRight());
        update();
    }
}



AnimNodeMgr::AnimNodeMgr():
    m_minX(0),
    m_minY(0),
    m_maxX(0),
    m_maxY(0)
{

}

AnimNodeMgr * AnimNodeMgr::getInstance()
{
    if(!pAnimNodeMgr)
    {
        pAnimNodeMgr = new AnimNodeMgr;
    }
    return pAnimNodeMgr;
}


AnimNode * AnimNodeMgr::add(uint32_t nodeId, qreal x, qreal y, QString nodeDescription)
{
    if(m_nodes.find(nodeId) != m_nodes.end())
    {
        //NS_FATAL_ERROR("NodeId:" << nodeId << " Already exists");
    }
    QPixmap pix(":/resources/ns3logo2.png","png");
    AnimNode * node = new AnimNode(nodeId, x, y, nodeDescription);
    node->setPos(x, y);
    //node->setPixmap(pix);
    m_nodes[nodeId] = node;
    m_minX = qMin (m_minX, x);
    m_minY = qMin (m_minY, y);
    m_maxX = qMax (m_maxX, x);
    m_maxY = qMax (m_maxY, y);

    return node;
}


AnimNode * AnimNodeMgr::getNode(uint32_t nodeId)
{
    return m_nodes[nodeId];
}

uint32_t
AnimNodeMgr::getCount()
{
    return m_nodes.size();
}


QPointF
AnimNodeMgr::getMinPoint()
{
    return QPointF (m_minX, m_minY);
}

QPointF
AnimNodeMgr::getMaxPoint()
{
    qreal m = qMax (m_maxX, m_maxY);
    return QPointF (m, m);
}



}


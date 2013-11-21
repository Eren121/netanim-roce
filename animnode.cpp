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

AnimNode::AnimNode(uint32_t nodeId, qreal x, qreal y):m_nodeDescription(0),
    m_nodeId(nodeId),
    m_x(x),
    m_y(y)
{
    //setVisible(false);
    setZValue(ANIMNODE_ZVALUE);
}

AnimNode::~AnimNode()
{
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

uint32_t
AnimNode::getNodeId()
{
    return m_nodeId;
}

QPointF AnimNode::getCenter()
{
    return sceneBoundingRect().center();
}
void AnimNode::setNodeDescription(QString description)
{
    if(!m_nodeDescription)
    {
        m_nodeDescription = new QGraphicsTextItem(description);
    }
    QGraphicsScene * s = scene();
    if(!s)
    {
        return;
    }
    s->addItem(m_nodeDescription);
    m_nodeDescription->setVisible(false);
}

void AnimNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ResizeableItem::paint(painter, option, widget);
    if(m_nodeDescription)
    {
        painter->save();
        QTransform viewTransform = AnimatorView::getInstance()->getTransform();
        QFont f = painter->font();
        //NS_LOG_DEBUG ("PointSize:" << f.pointSizeF());
        f.setPointSizeF(10/viewTransform.m22());
        painter->setFont(f);
        painter->drawText(m_width, m_height, m_nodeDescription->toPlainText());
        painter->restore();
    }
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


AnimNode * AnimNodeMgr::add(uint32_t nodeId, qreal x, qreal y)
{
    if(m_nodes.find(nodeId) != m_nodes.end())
    {
        NS_FATAL_ERROR("NodeId:" << nodeId << " Already exists");
    }
    QPixmap pix(":/resources/ns3logo2.png","png");
    AnimNode * node = new AnimNode(nodeId, x, y);
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
    return QPointF (m_maxX, m_maxY);
}



}


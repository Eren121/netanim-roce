#include <QPainter>
#include <QGraphicsScene>
#include "animnode.h"
#include "logqt.h"
#include "log.h"
#include "assert.h"

NS_LOG_COMPONENT_DEFINE("AnimNode");


AnimNodeMgr * pAnimNodeMgr = 0;

AnimNode::AnimNode(uint32_t nodeId):m_nodeDescription(0),
    m_nodeId(nodeId)
{

}

AnimNode::~AnimNode()
{
    QGraphicsScene * s = scene();
    NS_ASSERT(s);
    if(s)
    {
        if(m_nodeDescription)
        {
            s->removeItem(m_nodeDescription);
            delete m_nodeDescription;
        }
    }
}

void AnimNode::setNodeDescription(QString description)
{
    if(!m_nodeDescription)
    {
        m_nodeDescription = new QGraphicsTextItem(description);
    }
    //m_textItem->setFlags(QGraphicsItem::ItemIgnoresTransformations);
    QGraphicsScene * s = scene();
    if(!s)
    {
        return;
    }
    s->addItem(m_nodeDescription);
    m_nodeDescription->setPos(boundingRect().bottomRight());
}

void AnimNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ResizeableItem::paint(painter, option, widget);
    if(m_nodeDescription)
    {
        m_nodeDescription->setPos(sceneBoundingRect().bottomRight());
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



AnimNodeMgr::AnimNodeMgr()
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


AnimNode * AnimNodeMgr::add(uint32_t nodeId)
{
    QPixmap pix(":/new/prefix1/ns3logo2.png","png");
    AnimNode * node = new AnimNode(nodeId);// ResizeableItem;// new ResizeablePixmap(pix);
    node->setNodeDescription("Item1");
    node->setPos(nodeId * 355, 355);
    node->setPixmap(pix);
    return node;
}

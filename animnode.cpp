#include <QPainter>
#include <QGraphicsScene>
#include "animnode.h"
#include "logqt.h"
#include "log.h"

NS_LOG_COMPONENT_DEFINE("AnimNode");

AnimNode::AnimNode():m_nodeDescription(0)
{

}

AnimNode::~AnimNode()
{
    QGraphicsScene * s = scene();
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

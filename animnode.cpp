#include <QPainter>
#include <QGraphicsScene>
#include "animnode.h"
#include "logqt.h"
#include "log.h"

NS_LOG_COMPONENT_DEFINE("AnimNode");

AnimNode::AnimNode()
{

}

void AnimNode::init()
{
    m_textItem = new QGraphicsTextItem("Sample Text");
    scene()->addItem(m_textItem);
    m_textItem->setPos(boundingRect().bottomLeft());
}

void AnimNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ResizeableItem::paint(painter, option, widget);
    m_textItem->setPos(boundingRect().bottomLeft());

}


void AnimNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    ResizeableItem::mouseMoveEvent(event);
    NS_LOG_DEBUG("MouseMove");
    m_textItem->setPos(boundingRect().bottomLeft());
    update();
}

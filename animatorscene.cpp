#include "log.h"
#include "logqt.h"
#include "animatorscene.h"
#include "animnode.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include "timevalue.h"


using namespace ns3;
NS_LOG_COMPONENT_DEFINE("AnimatorScene");


AnimatorScene::AnimatorScene():QGraphicsScene(0, 0, ANIMATORSCENE_USERAREA_WIDTH, ANIMATORSCENE_USERAREA_WIDTH)
{
    m_userAreadWidth = ANIMATORSCENE_USERAREA_WIDTH;
    m_userAreaHeight = ANIMATORSCENE_USERAREA_HEIGHT;
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
    addRect(0, 0, m_userAreadWidth, m_userAreaHeight);
    addLine(m_userAreadWidth/2, 0, m_userAreadWidth/2, m_userAreaHeight);
    addLine(0, m_userAreaHeight/2, m_userAreadWidth, m_userAreaHeight/2);
    prepareTimeValueData();
}

void AnimatorScene::testSlot()
{
    //NS_LOG_DEBUG("Before:" << m_pItem->sceneBoundingRect() << " Pos:" << m_pItem->pos());
    //m_pItem->scale(1.5, 1.5);
    //NS_LOG_DEBUG("After:" << m_pItem->sceneBoundingRect() << " Pos:" << m_pItem->pos());
    //m_pItem->setSize(150, 20);
    views().last()->scale(1.1, 1.1);
}

void AnimatorScene::setUserAreaHeight(qreal h)
{
    m_userAreaHeight = h;
}

void AnimatorScene::setUserAreaWidth(qreal w)
{
    m_userAreadWidth = w;
}

void AnimatorScene::addPix()
{
    static int i = 0;
    addEllipse(i++, 15, 4, 4);

    AnimNodeMgr::getInstance()->add(0, this, m_userAreadWidth/2, m_userAreaHeight/2);
    AnimNodeMgr::getInstance()->getNode(0)->setNodeDescription("Item1");

    AnimNodeMgr::getInstance()->add(1, this, 155, 500);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item2");


    AnimNode * n0 =  AnimNodeMgr::getInstance()->getNode(0);
    AnimNode * n1 =  AnimNodeMgr::getInstance()->getNode(1);
    QLineF line(n0->getCenter(), n1->getCenter());
    QGraphicsLineItem * lineItem = new QGraphicsLineItem(line);
    addItem(lineItem);

}
void AnimatorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsView * view = views().last();
    //NS_LOG_DEBUG("Scene Mouse Move ScenePos:" << event->scenePos());
    //NS_LOG_DEBUG("Scene Mouse Move ScreenPos:" << event->screenPos());

    QPoint viewP = view->mapFromScene(event->scenePos());
    QPoint globalP = view->viewport()->mapToGlobal(viewP);
    //NS_LOG_DEBUG("Scene Mouse Move ViewPos:" << globalP);
    return QGraphicsScene::mouseMoveEvent(event);
}

void AnimatorScene::prepareTimeValueData()
{
    QVector<qreal> t ;
    t.push_back(0.0);
    t.push_back(1.0001);
    t.push_back(1.0004);
    t.push_back(1.0006);
    t.push_back(2.00001);
    t.push_back(3);
    t.push_back(4);
    t.push_back(4.5);
    t.push_back(4.51);
    for(QVector<qreal>::const_iterator i = t.begin();
        i != t.end();
        ++i)
    {
        m_testTimeValue.add(*i, QString::number(*i));
    }
    m_testTimeValue.setCurrentTime(0);
    NS_LOG_DEBUG(m_testTimeValue.getCurrent().data()->toAscii());
    m_testTimeValue.setCurrentTime(1);
    NS_LOG_DEBUG(m_testTimeValue.getCurrent().toDouble());
    m_testTimeValue.setCurrentTime(2);
    NS_LOG_DEBUG(m_testTimeValue.getCurrent().toDouble());
    NS_LOG_DEBUG(m_testTimeValue.getCurrent().toDouble());
    NS_LOG_DEBUG(m_testTimeValue.getCurrent().toDouble());

   // m_testTimeValue.setCurrentTime(2);



}

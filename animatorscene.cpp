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


AnimPacket * AnimatorScene::getTestPacket(qreal firstBitTx, qreal propDelay, qreal bitRate)
{
    qreal packetSize = 8 * 1024;
    qreal lastBitDelta = packetSize/bitRate;
    AnimPacket * p = new AnimPacket(0, 1, firstBitTx, firstBitTx + lastBitDelta, firstBitTx + propDelay, firstBitTx + propDelay +lastBitDelta );
    return p;

}

void AnimatorScene::displayPacket(qreal t)
{
    m_testTimeValue.setCurrentTime(t-2);
    NS_LOG_DEBUG(m_testTimeValue.getCurrent()->getFirstBitTx());
}


void AnimatorScene::prepareTimeValueData()
{
    qreal propDelay1 = 10e-3;
    qreal bitRate = 100 * 1024;
    qreal firstBitTx = 0;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 0.25;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 0.50;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 0.75;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 1.0;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 1.25;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 1.50;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 1.75;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 2.0;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 2.5;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 3.0;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 3.25;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 3.5;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 3.75;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 4.0;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));
    firstBitTx = 4.25;
    m_testTimeValue.add(firstBitTx, getTestPacket(firstBitTx, propDelay1, bitRate));

    displayPacket(0);
    displayPacket(1);
    displayPacket(2);
    displayPacket(3);
    displayPacket(3.1);
    displayPacket(4.75);




}

#include "log.h"
#include "logqt.h"
#include "animatorscene.h"
#include "animnode.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include "timevalue.h"
#include <math.h>
#include <string.h>
#include <sstream>


namespace ns3
{

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
    //views().last()->scale(1.1, 1.1);
    static qreal t = 0;
    displayPacket(t);
    t += 0.1;

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
    AnimNodeMgr::getInstance()->getNode(0)->setNodeDescription("Item0");

    AnimNodeMgr::getInstance()->add(1, this, 7 *m_userAreadWidth/8, m_userAreaHeight/2);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item1");

    AnimNodeMgr::getInstance()->add(2, this, 6 * m_userAreadWidth/8, m_userAreaHeight/4);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item2");

    AnimNodeMgr::getInstance()->add(3, this, m_userAreadWidth/2, m_userAreaHeight/8);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item3");

    AnimNodeMgr::getInstance()->add(4, this, m_userAreadWidth/4, m_userAreaHeight/8);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item4");

    AnimNodeMgr::getInstance()->add(5, this, m_userAreadWidth/8, m_userAreaHeight/2);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item5");

    AnimNodeMgr::getInstance()->add(6, this, m_userAreadWidth/4, 6 * m_userAreaHeight/8);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item6");

    AnimNodeMgr::getInstance()->add(7, this, m_userAreadWidth/2, 7* m_userAreaHeight/8);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item7");

    AnimNodeMgr::getInstance()->add(8, this, 6 *m_userAreadWidth/8, 6* m_userAreaHeight/8);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item8");


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


AnimPacket * AnimatorScene::getTestPacket(uint32_t fromNodeId, uint32_t toNodeId, qreal firstBitTx, qreal propDelay, qreal bitRate)
{
    qreal packetSize = 8 * 1024;
    qreal lastBitDelta = packetSize/bitRate;
    qreal l_firstBitTx = firstBitTx;
    qreal lastBitTx = firstBitTx + lastBitDelta;
    qreal firstBitRx = firstBitTx + propDelay;
    qreal lastBitRx = firstBitRx + lastBitDelta;

    AnimPacket * p = new AnimPacket(fromNodeId,
                                    toNodeId,
                                    l_firstBitTx,
                                    lastBitTx,
                                    firstBitRx,
                                    lastBitRx);
    addItem (p);
    return p;

}

void AnimatorScene::displayPacket(qreal t)
{

    m_testTimeValue.setCurrentTime(t);
    TimeValue<AnimPacket*>::TimeValueResult_t result;
    AnimPacket * p = m_testTimeValue.get(t, result);
    while (result == m_testTimeValue.GOOD)
    {
        p->update (t);
        NS_LOG_DEBUG ("Pos:" << p->getHead ());
        p->setPos(p->getHead ());
        //addEllipse(fromPos.x() + x, fromPos.y() + y, 5, 5);
        p = m_testTimeValue.get(t, result);
    }

}


void AnimatorScene::prepareTimeValueData()
{
    m_testTimeValue.setLookBack(11);
    qreal propDelay1 = 10; // 10s for test
    qreal bitRate = 100 * 1024; //100KBps

    qreal firstBitTx = 0;
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 1, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 2, firstBitTx, propDelay1, bitRate));

    firstBitTx = 0.3;
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 1, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 2, firstBitTx, propDelay1, bitRate));



    firstBitTx = 1;
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 1, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 2, firstBitTx, propDelay1, bitRate));


    firstBitTx = 1.2;
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 1, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 2, firstBitTx, propDelay1, bitRate));

    firstBitTx = 1.3;
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 1, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 2, firstBitTx, propDelay1, bitRate));

    firstBitTx = 2;
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 1, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 2, firstBitTx, propDelay1, bitRate));

    firstBitTx = 2.1;
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 1, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 2, firstBitTx, propDelay1, bitRate));

    //displayPacket(0);
    //displayPacket(0);

    //displayPacket(0.1);
    //displayPacket(0.1);

    //displayPacket(0.2);
    //displayPacket(0.7);
    //displayPacket(0.9);
    //displayPacket(1.0);
    //displayPacket(2.0);
    //displayPacket(2.2);
    //displayPacket(2.2);
    //displayPacket(7.2);
    //logQString(m_testTimeValue.isEnd());
    //displayPacket(0);

    /*
    displayPacket(0.1);
    displayPacket(0.2);
    displayPacket(0.3);
    displayPacket(0.5);
    displayPacket(0.7);
    displayPacket(1.3);
    displayPacket(5.0);
    displayPacket(8);
    displayPacket(9.9);
    displayPacket(10.0);
    displayPacket(11.0);
    */
    /*std::cout << m_testTimeValue.toString().str();*/
    fflush(stdout);
}

} // namespace ns3

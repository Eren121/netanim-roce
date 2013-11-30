#include "log.h"
#include "logqt.h"
#include "animatorscene.h"
#include "animnode.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QLabel>
#include "timevalue.h"
#include <math.h>
#include <string.h>
#include <sstream>


namespace netanim
{

NS_LOG_COMPONENT_DEFINE("AnimatorScene");
AnimatorScene * pAnimatorScene = 0;

AnimatorScene::AnimatorScene():QGraphicsScene(0, 0, ANIMATORSCENE_USERAREA_WIDTH, ANIMATORSCENE_USERAREA_WIDTH)
{
    m_userAreadWidth = ANIMATORSCENE_USERAREA_WIDTH;
    m_userAreaHeight = ANIMATORSCENE_USERAREA_HEIGHT;
    m_testButton = new QPushButton("Test");
    connect(m_testButton, SIGNAL(clicked()), this, SLOT(testSlot()));
    addWidget(m_testButton)->setPos(500, 500);
    QPixmap pix(":/resources/ns3logo2.png","png");

    m_background = new ResizeablePixmap(pix);
    m_background->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    m_background->setZValue(-100);
    //addItem(m_background);
    //testSlot();
    /*addPix();
    addRect(0, 0, m_userAreadWidth, m_userAreaHeight);
    addLine(m_userAreadWidth/2, 0, m_userAreadWidth/2, m_userAreaHeight);
    addLine(0, m_userAreaHeight/2, m_userAreadWidth, m_userAreaHeight/2);
    prepareTimeValueData();*/

    m_mousePositionLabel = new QLabel ("");
    m_mousePositionLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_mousePositionProxyWidget = addWidget(m_mousePositionLabel, Qt::ToolTip);
    m_mousePositionProxyWidget->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    //addItem(m_mousePositionLabel);

}


AnimatorScene *
AnimatorScene::getInstance()
{
    if(!pAnimatorScene)
    {
        pAnimatorScene = new AnimatorScene;
    }
    return pAnimatorScene;
}

void AnimatorScene::testSlot()
{

}

void AnimatorScene::setUserAreaHeight(qreal h)
{
    m_userAreaHeight = h;
}

void AnimatorScene::setUserAreaWidth(qreal w)
{
    m_userAreadWidth = w;
}


void
AnimatorScene::addWirelessCircle(AnimWirelessCircles *w)
{
    addItem(w);
    m_animatedWirelessCircles.push_back(w);
}

void
AnimatorScene::purgeAnimatedNodes()
{
    for(QVector <AnimNode*>::const_iterator i = m_animatedNodes.begin();
        i != m_animatedNodes.end();
        ++i)
    {
        AnimNode * animNode = *i;
        animNode->setVisible(false);
        QGraphicsTextItem * ti = animNode->getDescription();
        removeItem(animNode);
        removeItem(ti);
        delete animNode;
    }
    m_animatedNodes.clear();
    AnimNodeMgr::getInstance()->systemReset();

}

void
AnimatorScene::purgeAnimatedPackets()
{
    for(QVector <AnimPacket *>::const_iterator i = m_animatedPackets.begin();
        i != m_animatedPackets.end();
        ++i)
    {
        AnimPacket * p = *i;
        p->setVisible(false);
        removeItem (p->getInfoTextItem());
        removeItem(p);
        delete p;
    }
    m_animatedPackets.clear();

    for(QVector <AnimWirelessCircles *>::const_iterator i = m_animatedWirelessCircles.begin();
        i != m_animatedWirelessCircles.end();
        ++i)
    {
        AnimWirelessCircles * w = *i;
        w->setVisible(false);
        removeItem(w);
        delete w;
    }
    m_animatedWirelessCircles.clear();
}


void
AnimatorScene::addNode(AnimNode *animNode)
{
    addItem(animNode);
    m_animatedNodes.push_back(animNode);
    animNode->setPos(animNode->getX(), animNode->getY());
    addItem(animNode->getDescription());
    animNode->getDescription()->setPos(animNode->sceneBoundingRect().bottomRight());
    qreal boundaryWidth = AnimNodeMgr::getInstance()->getMaxPoint().x() * 0.1;
    QPointF minPoint = QPointF(AnimNodeMgr::getInstance()->getMinPoint().x() - boundaryWidth,
                        AnimNodeMgr::getInstance()->getMinPoint().y() - boundaryWidth);

    QPointF maxPoint = QPointF(AnimNodeMgr::getInstance()->getMaxPoint().x() + boundaryWidth,
                        AnimNodeMgr::getInstance()->getMaxPoint().y() + boundaryWidth);
    setSceneRect(QRectF (minPoint, maxPoint));


}

void
AnimatorScene::addPacket(AnimPacket *p)
{
    addItem(p);
    //addItem(p->getInfoTextItem());
    p->getInfoTextItem()->setPos(p->boundingRect().bottomLeft());
    m_animatedPackets.push_back(p);
}

void AnimatorScene::addPix()
{

}
void AnimatorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
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

   /* AnimPacket * p = new AnimPacket(fromNodeId,
                                    toNodeId,
                                    l_firstBitTx,
                                    lastBitTx,
                                    firstBitRx,
                                    lastBitRx);*/
    //addItem (p);
    return 0;

}

void AnimatorScene::displayPacket(qreal t)
{
    purgeAnimatedPackets();
    NS_LOG_DEBUG("Diplaying packet at t:" << t);
    m_testTimeValue.setCurrentTime(t);
    TimeValue<AnimPacket*>::TimeValueResult_t result;
    AnimPacket * p = m_testTimeValue.get(t, result);
    while (result == m_testTimeValue.GOOD)
    {
        m_animatedPackets.push_back(p);
        p->update (t);
        //NS_LOG_DEBUG ("Pos:" << p->getHead ());
        p->setPos(p->getHead ());
        p = m_testTimeValue.get(t, result);
        update();
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
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 3, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 4, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 5, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 6, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 7, firstBitTx, propDelay1, bitRate));
    m_testTimeValue.add(firstBitTx, getTestPacket(0, 8, firstBitTx, propDelay1, bitRate));

/*

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
    */

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

} // namespace netanim

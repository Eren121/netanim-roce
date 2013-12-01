#include "log.h"
#include "logqt.h"
#include "animatorscene.h"
#include "animatorview.h"
#include "animnode.h"
#include "animlink.h"
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

void
AnimatorScene::setShowInterfaceTexts(bool showIp, bool showMac)
{
    resetInterfaceTexts();
    m_showIpInterfaceTexts = showIp;
    m_showMacInterfaceTexts = showMac;
    if(!m_showIpInterfaceTexts && !m_showMacInterfaceTexts)
    {
        return;
    }
    if(!m_interfaceATexts.size())
    {
        for(LinkManager::NodeIdAnimLinkVectorMap_t::const_iterator i = LinkManager::getInstance()->getLinks()->begin();
            i != LinkManager::getInstance()->getLinks()->end();
            ++i)
        {

            LinkManager::AnimLinkVector_t linkVector = i->second;

            for(LinkManager::AnimLinkVector_t::const_iterator j = linkVector.begin();
                j != linkVector.end();
                ++j)
            {
                AnimLink * animLink = *j;

                QString pointADescription = animLink->getInterfaceADescription();
                QPointF pointApos = animLink->getInterfacePosA();
                AnimInterfaceText * interfaceAText = new AnimInterfaceText(pointADescription);
                interfaceAText->setPos(pointApos);
                addItem(interfaceAText);
                m_interfaceATexts.push_back(interfaceAText);
                interfaceAText->setMode(m_showIpInterfaceTexts, m_showMacInterfaceTexts);

                QString pointBDescription = animLink->getInterfaceBDescription();
                if(pointBDescription == "")
                {
                    continue;
                }
                QPointF pointBpos = animLink->getInterfacePosB();
                AnimInterfaceText * interfaceBText = new AnimInterfaceText(pointBDescription, true);
                interfaceBText->setMode(m_showIpInterfaceTexts, m_showMacInterfaceTexts);
                addItem(interfaceBText);
                interfaceBText->setPos(pointBpos);
                m_interfaceBTexts.push_back(interfaceBText);
            }
        }
        update();
        removeInterfaceTextCollision();
        return;
     }
    for(AnimInterfaceTextVector_t::const_iterator i = m_interfaceATexts.begin();
        i != m_interfaceATexts.end();
        ++i)
    {
        AnimInterfaceText * interfaceText = *i;
        interfaceText->setMode(m_showIpInterfaceTexts, m_showMacInterfaceTexts);
        QGraphicsLineItem * l = interfaceText->getLine();
        if(l)
        {
            l->setVisible(showIp || showMac);
        }
        interfaceText->setVisible(showIp || showMac);
    }
    for(AnimInterfaceTextVector_t::const_iterator i = m_interfaceBTexts.begin();
        i != m_interfaceBTexts.end();
        ++i)
    {
        AnimInterfaceText * interfaceText = *i;
        interfaceText->setMode(m_showIpInterfaceTexts, m_showMacInterfaceTexts);
        QGraphicsLineItem * l = interfaceText->getLine();
        if(l)
        {
            l->setVisible(showIp || showMac);
        }
        interfaceText->setVisible(showIp || showMac);
    }
    removeInterfaceTextCollision();
    update();
}


QList <QGraphicsItem *>
AnimatorScene::getInterfaceTextCollisionList(AnimInterfaceText * text)
{
    QList <QGraphicsItem *> l = text->collidingItems();
    QList <QGraphicsItem *> collidingList;
    for (QList <QGraphicsItem *>::const_iterator i = l.begin();
         i != l.end();
         ++i)
    {
        QGraphicsItem * item = *i;
        if(item->type() == (ANIMINTERFACE_TEXT_TYPE))
        {
            collidingList.append(item);
        }
    }
    return collidingList;
}


void
AnimatorScene::repositionInterfaceText(AnimInterfaceText *textItem)
{
    bool isRight = textItem->pos().x() > (sceneRect().width()/2);
    QPointF oldPos = textItem->pos();
    QFontMetrics fm(font());
    QPointF newPos;
    if(!isRight)
    {
        textItem->setLeftAligned(false);
        qreal y = m_leftTop + 1.5 * fm.height()/AnimatorView::getInstance()->transform().m11();
        newPos = QPointF(-fm.width(textItem->getText())/AnimatorView::getInstance()->transform().m11(), y);
        m_leftTop = newPos.y();
    }
    else
    {
        textItem->setLeftAligned(true);
        qreal y = m_rightTop + 1.5 * fm.height()/AnimatorView::getInstance()->transform().m11();
        newPos = QPointF(sceneRect().width() + fm.width(textItem->getText())/AnimatorView::getInstance()->transform().m11(), y);
        m_rightTop = newPos.y();
    }
    textItem->setPos(newPos);
    QLineF l(oldPos, newPos);
    if(textItem->setLine(l))
    {
        addItem(textItem->getLine());
    }

}

void
AnimatorScene::resetInterfaceTexts()
{
    resetInterfaceTextTop();
    for(AnimInterfaceTextVector_t::const_iterator i = m_interfaceATexts.begin();
        i != m_interfaceATexts.end();
        ++i)
    {
        AnimInterfaceText * text = *i;
        QGraphicsLineItem * l = text->getLine();
        if(l)
        {
            removeItem(l);
        }
        removeItem(*i);
        delete (*i);
    }
    m_interfaceATexts.clear();
    for(AnimInterfaceTextVector_t::const_iterator i = m_interfaceBTexts.begin();
        i != m_interfaceBTexts.end();
        ++i)
    {
        AnimInterfaceText * text = *i;
        QGraphicsLineItem * l = text->getLine();
        if(l)
        {
            removeItem(l);
        }
        removeItem(*i);
        delete (*i);
    }
    m_interfaceBTexts.clear();
    update();
}

void
AnimatorScene::resetInterfaceTextTop()
{
    m_leftTop = 0;
    m_rightTop = 0;
}

void
AnimatorScene::removeInterfaceTextCollision()
{


    for(AnimInterfaceTextVector_t::iterator i = m_interfaceATexts.begin();
        i != m_interfaceATexts.end();
        ++i)
    {
        AnimInterfaceText * text = *i;
        QList <QGraphicsItem *> collidingList = getInterfaceTextCollisionList(text);
        //qDebug(collidingList.count(), "CL count");
        if(collidingList.count())
        {
            repositionInterfaceText(text);
        }

    }
    for(AnimInterfaceTextVector_t::iterator i = m_interfaceBTexts.begin();
        i != m_interfaceBTexts.end();
        ++i)
    {
        AnimInterfaceText * text = *i;
        QList <QGraphicsItem *> collidingList = getInterfaceTextCollisionList(text);
        //qDebug(collidingList.count(), "CL count");
        if(collidingList.count())
        {
            repositionInterfaceText(text);
        }
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

AnimInterfaceText::AnimInterfaceText(QString description, bool leftAligned):QGraphicsTextItem(description),
    m_leftAligned(leftAligned),
    m_line(0)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setZValue(ANIMINTERFACE_TEXT_TYPE);
}

AnimInterfaceText::~AnimInterfaceText()
{
    if(m_line)
    {
        delete m_line;
    }
}

void
AnimInterfaceText::setLeftAligned(bool leftAligned)
{
    m_leftAligned = leftAligned;
}

QPainterPath
AnimInterfaceText::shape() const
{
    QPainterPath p;
    QFontMetrics fm(font());
    QRectF r(0, 0, fm.width(getText())/AnimatorView::getInstance()->transform().m11(),
             fm.height()/AnimatorView::getInstance()->transform().m11());
    p.addRect(r);
    return p;
}

QString
AnimInterfaceText::getText() const
{
    QStringList parts = toPlainText().split('~');
    if(m_mode == AnimInterfaceText::IPV4)
    {
        return parts.at(0);
    }
    if(m_mode == AnimInterfaceText::MAC)
    {
        if(parts.length() != 2)
        {
            return "";
        }
        return parts.at(1);
    }
    return toPlainText();
}


void
AnimInterfaceText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(m_leftAligned)
    {
        QFontMetrics fm = painter->fontMetrics();
        QPointF leftAlignPoint = QPointF(-fm.width(getText()), 0);
        painter->save();
        painter->translate(leftAlignPoint);
        painter->drawText(QPointF(0, 0), getText());
        //QGraphicsTextItem::paint(painter, option, widget);
        painter->restore();
    }
    else
    {
        //QGraphicsTextItem::paint(painter, option, widget);
        painter->drawText(QPointF(0, 0), getText());

    }
}

bool
AnimInterfaceText::setLine(QLineF l)
{
    bool newLine = false;
    if(!m_line)
    {
        m_line = new QGraphicsLineItem;
        newLine = true;
    }
    QPen p;

    p.setColor(QColor(0, 0, 255, 50));
    m_line->setPen(p);
    m_line->setLine(l);
    return newLine;
}

QGraphicsLineItem *
AnimInterfaceText::getLine()
{
    return m_line;
}

void
AnimInterfaceText::setMode(bool showIpv4, bool showMac)
{
    if(!showIpv4 && !showMac)
    {
        m_mode = AnimInterfaceText::NONE;
    }
    if(showIpv4 && !showMac)
    {
        m_mode = AnimInterfaceText::IPV4;
    }
    if(!showIpv4 && showMac)
    {
        m_mode = AnimInterfaceText::MAC;
    }
    if(showIpv4 && showMac)
    {
        m_mode = AnimInterfaceText::BOTH;
    }
}



} // namespace netanim

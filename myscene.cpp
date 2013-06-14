#include "log.h"
#include "logqt.h"
#include "myscene.h"
#include "animnode.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QGraphicsLineItem>


using namespace ns3;
NS_LOG_COMPONENT_DEFINE("MyScene");


void QDEBUG(QPointF p, QString prefix)
{
    QString str = "X:" + QString::number(p.x()) + " Y:" + QString::number(p.y());
    QDEBUG(prefix + ":" + str);
}

void QDEBUG(QString str)
{
    str = "QD:" + str;
    qDebug(str.toAscii());
}







myscene::myscene():QGraphicsScene(0, 0, 1000, 1000)
{
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
}

void myscene::testSlot()
{
    //NS_LOG_DEBUG("Before:" << m_pItem->sceneBoundingRect() << " Pos:" << m_pItem->pos());
    //m_pItem->scale(1.5, 1.5);
    //NS_LOG_DEBUG("After:" << m_pItem->sceneBoundingRect() << " Pos:" << m_pItem->pos());
    //m_pItem->setSize(150, 20);
    views().last()->scale(1.1, 1.1);
}

void myscene::addPix()
{
    static int i = 0;
    addEllipse(i++, 15, 4, 4);

    AnimNodeMgr::getInstance()->add(0, this, 355, 500);
    AnimNodeMgr::getInstance()->getNode(0)->setNodeDescription("Item1");

    AnimNodeMgr::getInstance()->add(1, this, 155, 500);
    AnimNodeMgr::getInstance()->getNode(1)->setNodeDescription("Item2");


    AnimNode * n0 =  AnimNodeMgr::getInstance()->getNode(0);
    AnimNode * n1 =  AnimNodeMgr::getInstance()->getNode(1);
    QLineF line(n0->getCenter(), n1->getCenter());
    QGraphicsLineItem * lineItem = new QGraphicsLineItem(line);
    addItem(lineItem);

}
void myscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsView * view = views().last();
    //NS_LOG_DEBUG("Scene Mouse Move ScenePos:" << event->scenePos());
    //NS_LOG_DEBUG("Scene Mouse Move ScreenPos:" << event->screenPos());

    QPoint viewP = view->mapFromScene(event->scenePos());
    QPoint globalP = view->viewport()->mapToGlobal(viewP);
    //NS_LOG_DEBUG("Scene Mouse Move ViewPos:" << globalP);
    return QGraphicsScene::mouseMoveEvent(event);
}

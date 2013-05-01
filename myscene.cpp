#include "myscene.h"
#include <QGraphicsProxyWidget>

myscene::myscene()
{
    m_testButton = new QPushButton("Test");
    connect(m_testButton, SIGNAL(clicked()), this, SLOT(testSlot()));
    addWidget(m_testButton);
    QPixmap pix("/Users/john/ns-3/newcanvas1/ns3logo2.png","png");
    m_background = addPixmap(pix);
    m_background->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    m_background->setZValue(-100);

}


void myscene::testSlot()
{
    static int i = 0;
    addEllipse(i++, 15, 4, 4);
    qDebug("Hi");
}

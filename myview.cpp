#include "log.h"
#include "logqt.h"
#include "myview.h"
using namespace ns3;

#include <QMouseEvent>
NS_LOG_COMPONENT_DEFINE("MyView");

myview::myview(QWidget *parent) :
    QGraphicsView(parent)
{
}

void
myview::resizeEvent(QResizeEvent *event)
{
    return;
    QGraphicsView::resizeEvent(event);
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    qDebug("Resizing");

}


void
myview::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
    //scale(2,2);
}
void
myview::mouseMoveEvent(QMouseEvent *event)
{
    NS_LOG_DEBUG("myview::MouseMove:" << event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

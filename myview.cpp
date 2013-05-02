#include "myview.h"

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

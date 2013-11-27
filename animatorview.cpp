/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: John Abraham <john.abraham@gatech.edu>
 */


#include "animatorview.h"
#include "animatorscene.h"
#include "logqt.h"

#include <QtGui/QGraphicsScene>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QFileDialog>
#include "resizeableitem.h"

namespace netanim {

NS_LOG_COMPONENT_DEFINE ("AnimatorView");
AnimatorView * pAnimatorView = 0;

AnimatorView::AnimatorView(QGraphicsScene * scene) :
    QGraphicsView(scene),
    m_currentZoomFactor(1),
    m_resizing(false),
    m_resizeItemSceneWidth(0),
    m_inResizingBoundary(false)
{
    setRenderHint(QPainter::Antialiasing);
}

AnimatorView *
AnimatorView::getInstance()
{
    if(!pAnimatorView)
    {
        pAnimatorView = new AnimatorView(AnimatorScene::getInstance());
    }
    return pAnimatorView;
}

void
AnimatorView::paintEvent(QPaintEvent *event)
{
    //qDebug(transform);
    QGraphicsView::paintEvent(event);
}


void
AnimatorView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
}

void
AnimatorView::mousePressEvent(QMouseEvent *event)
{
    if (m_inResizingBoundary)
    {
        m_resizing = true;
    }
    QGraphicsView::mousePressEvent(event);
}

void
AnimatorView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_resizing)
    {
        QPointF mouseReleasePos = mapToScene(event->pos());
        QPointF itemCenter = m_resizeItemSceneRect.center();
        qreal distance = qAbs (itemCenter.x() - mouseReleasePos.x());
        ResizeableItem * resizeableItem = static_cast <ResizeableItem *> (m_resizingItem);
        resizeableItem->setWidth(distance * 2);
    }
    m_resizing = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void
AnimatorView::mouseMoveEvent(QMouseEvent * event)
{
    scene()->invalidate();
    if (m_resizing)
    {
        QPointF mouseReleasePos = mapToScene(event->pos());
        QPointF itemCenter = m_resizeItemSceneRect.center();
        qreal distance = qAbs (itemCenter.x() - mouseReleasePos.x());
        ResizeableItem * resizeableItem = static_cast <ResizeableItem *> (m_resizingItem);
        resizeableItem->setWidth(distance * 2);
        m_resizeItemSceneRect = resizeableItem->sceneBoundingRect();
        QGraphicsView::mouseMoveEvent(event);

        return;
    }
//    QList <QGraphicsItem *> listOfItems = items(mapToScene ((event->pos())));
    QPoint p (event->pos().x(), event->pos().y());
    QPointF p3 = mapToScene(p);
    QPoint p2 (p3.x(), p3.y());
    QList <QGraphicsItem *> listOfItems = items(p);

    foreach(QGraphicsItem * item, listOfItems)
    {
        if (item->type() == ANIMNODE_TYPE)
        {
            NS_LOG_DEBUG ("DblClicked AnimNode:" << item->sceneBoundingRect());
            m_resizeItemSceneWidth = item->sceneBoundingRect().width();
            m_resizeItemSceneRect = item->sceneBoundingRect();
            m_resizingItem = item;
            break;
        }
    }
    QCursor c;

        NS_LOG_DEBUG ("Mouse Move:" << mapToScene(event->pos()));
        qreal eventPosX = mapToScene(event->pos()).x();
        qreal itemRectRightX = m_resizeItemSceneRect.right();
        qreal lowerBoundX = itemRectRightX - (m_resizeItemSceneWidth * 0.05);
        qreal upperBoundX = itemRectRightX + (m_resizeItemSceneWidth * 0.05);
        NS_LOG_DEBUG ("lower bound X:" << lowerBoundX << " upper bound X:" << upperBoundX);
        if ( (eventPosX >= lowerBoundX) && (eventPosX <= upperBoundX) )
        {
            NS_LOG_DEBUG ("Setting cursor");
            c.setShape(Qt::SizeHorCursor);
            setCursor(c);
            m_inResizingBoundary = true;
        }
        else
        {
            if (!m_resizing)
            {
                c.setShape(Qt::ArrowCursor);
                setCursor(c);

            }
            m_inResizingBoundary = false;
        }

    QGraphicsView::mouseMoveEvent(event);
}

void
AnimatorView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
}


AnimatorScene *
AnimatorView::getAnimatorScene()
{
    return  AnimatorScene::getInstance();
}

void
AnimatorView::updateTransform()
{

}

void
AnimatorView::setCurrentZoomFactor(qreal factor)
{
    if (m_currentZoomFactor < factor)
    {
        scale(1.1, 1.1);
    }
    else
    {
        scale(0.9, 0.9);
    }
    m_currentZoomFactor = factor;
    update();
}

void
AnimatorView::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
    update();
}

void
AnimatorView::save()
{
}

void
AnimatorView::fitSceneWithinView()
{
    updateTransform();
}

void
AnimatorView::systemReset()
{
    m_currentZoomFactor = 1;

    resetTransform();
}

void
AnimatorView::postParse()
{

    //fitInView(AnimatorScene::getInstance()->sceneRect());
    //NS_LOG_DEBUG ("View Transform:" << transform());



         QTransform t;



         qreal minDimension = qMin(getAnimatorScene()->width(), getAnimatorScene()->height());



         qreal xScale = width()/minDimension;

         qreal yScale = height()/minDimension;

         //qDebug(width(), "Width");

         //qDebug(height(), "height");

         qreal minScale = qMin(xScale, yScale);

         t.scale(minScale, minScale);

        // getAnimatorScene()->setCurrentScale(minScale, minScale);

         setTransform(t);
         NS_LOG_DEBUG ("View Transform:" << transform());



}

QTransform
AnimatorView::getTransform()
{
    return transform();
}

int
AnimatorView::getCurrentZoomFactor()
{
    return m_currentZoomFactor;
}

} // namespace netanim


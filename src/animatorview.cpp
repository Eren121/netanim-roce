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
 * Author: John Abraham <john.abraham.in@gmail.com>
 */


#include "animatorview.h"

namespace netanim
{

NS_LOG_COMPONENT_DEFINE ("AnimatorView");
AnimatorView * pAnimatorView = 0;

AnimatorView::AnimatorView (QGraphicsScene * scene) :
  QGraphicsView (scene),
  m_currentZoomFactor (1)

{
  setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
  setViewportUpdateMode (BoundingRectViewportUpdate);
}

AnimatorView *
AnimatorView::getInstance ()
{
  if (!pAnimatorView)
    {
      pAnimatorView = new AnimatorView (AnimatorScene::getInstance ());
    }
  return pAnimatorView;
}

void
AnimatorView::paintEvent (QPaintEvent *event)
{
  //qDebug (transform);
  try
    {
      QGraphicsView::paintEvent (event);
    }
  catch (...)
    {

    }
}

AnimatorScene *
AnimatorView::getAnimatorScene ()
{
  return  AnimatorScene::getInstance ();
}

void
AnimatorView::setCurrentZoomFactor (qreal factor)
{
  if (m_currentZoomFactor < factor)
    {
      scale (1.1, 1.1);
    }
  else if(m_currentZoomFactor > factor)
    {
      scale (0.9, 0.9);
    }
  m_currentZoomFactor = factor;
  //update ();
}

void
AnimatorView::wheelEvent (QWheelEvent *event)
{
  if(QApplication::keyboardModifiers() & Qt::ControlModifier) {
    int delta = event->angleDelta().y();
    if(delta > 0) {
      setCurrentZoomFactor (m_currentZoomFactor + 1);
    }
    else if(delta < 0) {
      setCurrentZoomFactor (m_currentZoomFactor -  1);
    } 
  }
  else {
    QGraphicsView::wheelEvent (event);
  }

  update ();
}

void AnimatorView::mouseMoveEvent(QMouseEvent *event)
{
  if(cursor() == Qt::PointingHandCursor) {
    QPoint mouse(event->x(), event->y());
    QPoint delta(m_lastMousePos - mouse);
    m_lastMousePos = mouse;

    QRect center = viewport()->rect();
    center.translate(delta);
    QPointF target = mapToScene(center).boundingRect().center();
    centerOn(target);
  }

  QGraphicsView::mouseMoveEvent (event);
}

void AnimatorView::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::MiddleButton) {
    setCursor(Qt::PointingHandCursor);
    m_lastMousePos = QPoint(event->x(), event->y());
  }
  else {
    QGraphicsView::mousePressEvent (event);
  }
}

void AnimatorView::mouseReleaseEvent(QMouseEvent *event)
{
  if(event->button() == Qt::MiddleButton) {
    setCursor(Qt::ArrowCursor);
  }
  else {
    QGraphicsView::mouseReleaseEvent (event);
  }
}

void
AnimatorView::fitSceneWithinView ()
{
  QGraphicsView::fitInView (sceneRect (), Qt::KeepAspectRatio);

}

void
AnimatorView::systemReset ()
{
  m_currentZoomFactor = 1;

  resetTransform ();
}

void
AnimatorView::postParse ()
{

  fitSceneWithinView ();
}


} // namespace netanim


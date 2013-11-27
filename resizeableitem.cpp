/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006,2007 INRIA
 *
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
 */

#include <QCursor>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

#include "resizeableitem.h"
#include "logqt.h"
#include "log.h"

NS_LOG_COMPONENT_DEFINE("ResizeableItem");

ResizeableItem::ResizeableItem():
    m_mousePressed(false),
    m_currentResizeDirection(RESIZE_NOTRESIZING),
    m_lastResizeDirection(RESIZE_NOTRESIZING),
    m_resizing(false),
    m_type(ResizeableItem::CIRCLE),
    m_width(1),
    m_height(1),
    m_pixmap(0),
    m_r(255),
    m_g(0),
    m_b(0),
    m_alpha(240)
{
    //NS_LOG_FUNCTION(m_mousePressed);
    setAcceptsHoverEvents(true);
}

ResizeableItem::~ResizeableItem()
{
    if (m_pixmap)
    {
        delete m_pixmap;
    }

}

void ResizeableItem::setPixmap(QPixmap pix)
{
    m_pixmap = new QPixmap(pix);
    setType(ResizeableItem::PIXMAP);
}

void ResizeableItem::setType(ResizeableItemType_t t)
{
    m_type = t;
}

void
ResizeableItem::setWidth(qreal width)
{
    m_width = width;
}
void ResizeableItem::setSize(qreal width, qreal height)
{
    qreal xScale = width/sceneBoundingRect().width();
    qreal yScale = height/sceneBoundingRect().height();
    scale(xScale, yScale);
}
void ResizeableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePressed = true;
    QGraphicsItem::mousePressEvent(event);
}

void ResizeableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch(m_type)
    {
        case ResizeableItem::RECTANGLE:
            painter->drawRect(0, 0, m_width, m_height);
            break;
        case ResizeableItem::CIRCLE:
            {
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(QColor (m_r, m_g, m_b, m_alpha));
            painter->setBrush(brush);
            painter->drawEllipse(0, 0, m_width, m_height);
            }
            break;
        case ResizeableItem::PIXMAP:
            if (m_pixmap)
            {
                painter->drawPixmap(0, 0, m_width, m_height, *m_pixmap);
                painter->drawRect(0, 0, m_width, m_height);
            }
            break;
    }
}

bool ResizeableItem::isResizing()
{
    return (m_currentResizeDirection == m_lastResizeDirection);
}
void ResizeableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_mousePressed || !isResizing())
        return;
    qreal eventPosX = mapToScene(event->pos()).x() - (sceneBoundingRect().topLeft()).x();
    qreal eventPosY = mapToScene(event->pos()).y() - (sceneBoundingRect().topLeft()).y();
    if ((m_currentResizeDirection == RESIZE_RIGHT))
    {
        qreal xScale = eventPosX/getItemWidth();
        if(((xScale < 1) && (eventPosX < (PIXMAP_WIDTH_MIN))))
        {
            return;
        }
        if(xScale > 0)
        {
            //scale(xScale, 1);
            m_width = eventPosX;
        }

    }
    if ((m_currentResizeDirection == RESIZE_LEFT))
    {
        qreal xScale = (getItemWidth() - eventPosX)/getItemWidth();
        if(((xScale < 1) && (eventPosX < (PIXMAP_WIDTH_MIN))))
        {
            return;
        }
        //NS_LOG_DEBUG(xScale);

        qreal savedY = pos().y();
        if(xScale > 0)
        {
            scale(xScale, 1);
            m_width = m_width * xScale;

            setPos(QPointF(mapToScene(event->pos())).x(), savedY);
        }

    }
    if ((m_currentResizeDirection == RESIZE_TOP))
    {

        qreal yScale = (getItemHeight()- eventPosY)/getItemHeight();
        if(((yScale < 1) && (eventPosY < (PIXMAP_WIDTH_MIN))))
        {
            return;
        }
        qreal savedX = pos().x();
        if(yScale > 0)
        {
            scale(1, yScale);
            setPos(savedX, QPointF(mapToScene(event->pos())).y());

        }
    }
    if ((m_currentResizeDirection == RESIZE_BOTTOM))
    {

        qreal yScale = eventPosY/getItemHeight();
        if(((yScale < 1) && (eventPosY < (PIXMAP_WIDTH_MIN))))
        {
            return;
        }
        if(yScale > 0)
        {
            scale(1, yScale);
        }
    }
    QGraphicsItem::mouseMoveEvent(event);

}

qreal ResizeableItem::getItemWidth()
{
    return sceneBoundingRect().width();
}

qreal ResizeableItem::getItemHeight()
{
    return sceneBoundingRect().height();
}

void ResizeableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePressed = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void ResizeableItem::setResizingDirection(ResizeDirection_t direction)
{/*
    QCursor c;
    switch (direction)
    {

        case RESIZE_BOTTOM:
        case RESIZE_TOP:
            c.setShape(Qt::SizeVerCursor);
            setFlags(QGraphicsItem::ItemIsSelectable);
            break;
        case RESIZE_LEFT:
        case RESIZE_RIGHT:
            c.setShape(Qt::SizeHorCursor);
            setFlags(QGraphicsItem::ItemIsSelectable);
            break;
        case RESIZE_NOTRESIZING:
            c.setShape(Qt::OpenHandCursor);
            setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    }
    setCursor(c);
    m_currentResizeDirection = direction;*/
}

qreal ResizeableItem::getBorderWidth()
{
    QGraphicsView * view = scene()->views().last();
    QPointF scenePos1 = view->mapToScene(QPointF(0, 0).toPoint());
    QPointF scenePos2 = view->mapToScene(QPointF(PIXMAP_RESIZING_BORDER, 0).toPoint());
    //return qAbs(scenePos2.x() - scenePos1.x());
    return qAbs (sceneBoundingRect().width() * 0.1);
}

void ResizeableItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

    qreal borderWidth = getBorderWidth() ;
    qreal bottomRightX = sceneBoundingRect().bottomRight().x();
    qreal bottomRightXLow = bottomRightX - borderWidth;
    qreal bottomLeftX = sceneBoundingRect().bottomLeft().x();

    qreal bottomRightY = sceneBoundingRect().bottomRight().y();
    qreal bottomRightYLow = bottomRightY - borderWidth;
    qreal topLeftY = sceneBoundingRect().topLeft().y();

    qreal eventPosX = (mapToScene(event->pos())).x();
    qreal eventPosY = (mapToScene(event->pos())).y();
    if (((eventPosX >= bottomRightXLow) && (eventPosX <= bottomRightX)))
    {
        setResizingDirection(RESIZE_RIGHT);
    }
    else if (eventPosX <= (bottomLeftX+borderWidth))
    {
        setResizingDirection(RESIZE_LEFT);
    }
    else if (((eventPosY >= bottomRightYLow) && (eventPosY <= bottomRightY)))
    {
        setResizingDirection(RESIZE_BOTTOM);
    }
    else if (eventPosY <= (topLeftY+borderWidth))
    {
        setResizingDirection(RESIZE_TOP);
    }
    else
    {
        setResizingDirection(RESIZE_NOTRESIZING);
    }
    QGraphicsItem::hoverMoveEvent(event);
    m_lastResizeDirection = m_currentResizeDirection;
}

QRectF ResizeableItem::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}



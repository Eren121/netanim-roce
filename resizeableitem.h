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

#ifndef RESIZEABLEITEM_H
#define RESIZEABLEITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


#define PIXMAP_RESIZING_BORDER 5
#define PIXMAP_WIDTH_MIN 20

class ResizeableItem : public QGraphicsItem
{

public:
    typedef enum {
        RESIZE_RIGHT,
        RESIZE_LEFT,
        RESIZE_TOP,
        RESIZE_BOTTOM,
        RESIZE_NOTRESIZING
    } ResizeDirection_t;
    typedef enum {
        RECTANGLE,
        CIRCLE,
        PIXMAP
    } ResizeableItemType_t;
    ResizeableItem();
    ~ResizeableItem();
    QRectF boundingRect() const;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    qreal getItemWidth();
    qreal getItemHeight();
    qreal getBorderWidth();
    void setSize(qreal width, qreal height);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void setPixmap(QPixmap pix);
    void setType(ResizeableItemType_t t);

protected:
    qreal m_width;
    qreal m_height;
private:
    bool m_mousePressed;
    ResizeDirection_t m_currentResizeDirection;
    ResizeDirection_t m_lastResizeDirection;
    bool m_resizing;
    ResizeableItemType_t m_type;
    QPixmap * m_pixmap;
    bool isResizing();
    void setResizingDirection(ResizeDirection_t direction);

};

#endif // RESIZEABLEITEM_H

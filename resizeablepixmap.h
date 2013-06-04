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

#ifndef RESIZEABLEPIXMAP_H
#define RESIZEABLEPIXMAP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>


#define PIXMAP_RESIZING_BORDER 5
#define PIXMAP_WIDTH_MIN 20

class ResizeablePixmap : public QGraphicsPixmapItem
{

public:
    typedef enum {
        RESIZE_RIGHT,
        RESIZE_LEFT,
        RESIZE_TOP,
        RESIZE_BOTTOM,
        RESIZE_NOTRESIZING
    } ResizeDirection_t;
    ResizeablePixmap(QPixmap pix);
    QRectF boundingRect() const;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    qreal getItemWidth();
    qreal getItemHeight();
    qreal getBorderWidth();
    void setSize(qreal width, qreal height);

private:
    bool m_mousePressed;
    ResizeDirection_t m_currentResizeDirection;
    ResizeDirection_t m_lastResizeDirection;
    bool m_resizing;
    bool isResizing();
    void setResizingDirection(ResizeDirection_t direction);

};

#endif // RESIZEABLEPIXMAP_H

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

#include "graphpacket.h"
#include "packetsview.h"

namespace netanim {
#define PI 3.14159265


GraphPacket::GraphPacket (QPointF fromNodePos, QPointF toNodePos):
  m_fromNodePos (fromNodePos),
  m_toNodePos (toNodePos)
{
  QLineF l (fromNodePos, toNodePos);
  setLine (l);
}

void
GraphPacket::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPointF fromPos = line().p1();
  QPointF toPos = line().p2();
  QLineF l = QLineF (mapToScene (fromPos), mapToScene (toPos));
  painter->save ();
  QPainterPath arrowTailPath;
  arrowTailPath.moveTo (0, 0);
  arrowTailPath.lineTo (l.length () , 0);
  QPen p;
  p.setColor (Qt::blue);
  painter->setPen (p);
  painter->setPen (p);
  painter->rotate (360 - l.angle ());
  painter->drawPath (arrowTailPath);
  painter->restore();
  painter->save();

  painter->translate(0, 0);
  painter->rotate (360 - l.angle ());
  painter->translate (l.length(), 0);
  painter->drawEllipse (0, 0, 50, 50);
  painter->restore ();

  painter->save();
  painter->translate(0, 0);
  //painter->rotate(360 - l.angle());
  painter->restore();

  QPolygonF arrowHeadPolygon;
  QPainterPath arrowHeadPath;
  qreal arrowHeadLength = 0.005;//2 * (10/PacketsView::getInstance ()->transform().m22 ());
  arrowHeadPolygon << mapToScene (line().p1())
                   << mapToScene (line().p2());
                   //<< QPointF (-arrowHeadLength * cos (PI/4), -arrowHeadLength * sin (PI/4))
                   //<< QPointF (-arrowHeadLength * cos (PI/4), arrowHeadLength * sin (PI/4));

  arrowHeadPath.lineTo (-arrowHeadLength * cos (PI/10), -arrowHeadLength * sin (PI/10));
  arrowHeadPath.moveTo (l.length (), 0);
  arrowHeadPath.lineTo (-arrowHeadLength * cos (PI/10), arrowHeadLength * sin (PI/10));
  arrowHeadPath.moveTo (0, 0);

  painter->save();
  QPen arrowHeadPen;
  QColor black (0, 0, 5, 130);
  arrowHeadPen.setColor(black);


  painter->setPen(arrowHeadPen);
  //painter->rotate (360 - l.angle ());
  QBrush brush;
  brush.setColor (black);
  brush.setStyle (Qt::SolidPattern);
  painter->setBrush (brush);
  painter->translate (toPos);
  //painter->drawEllipse (0, 0, 10, 10);
  //painter->drawPolygon (arrowHeadPolygon);
  painter->restore ();


}

}

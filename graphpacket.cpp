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
  painter->translate(0, 0);
  painter->rotate (360 - l.angle ());
  //painter->rotate (l.angle());
  painter->save ();
  QPainterPath arrowTailPath;
  arrowTailPath.moveTo (0, 0);
  arrowTailPath.lineTo (l.length (), 0);
  QPen p;
  p.setColor (Qt::blue);
  painter->setPen (p);
  painter->setPen (p);
  painter->drawPath (arrowTailPath);
  painter->restore();


  painter->save();
  painter->translate (l.length(), 0);
  qreal angle = PI/4;
  qreal mag = 9;
  painter->drawLine (0, 0, -mag * cos (angle), mag * sin (angle));
  painter->drawLine (0, 0, -mag * cos (angle), -mag * sin (angle));
  painter->restore ();


}

}

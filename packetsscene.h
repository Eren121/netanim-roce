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

#ifndef PACKETSSCENE_H
#define PACKETSSCENE_H

#include "common.h"
namespace netanim {

class PacketsScene: public QGraphicsScene {

public:
  static PacketsScene * getInstance ();
  void addPackets ();
private:
  PacketsScene ();
  bool setUpNodeLines ();
  qreal timeToY (qreal t);
  void addPacket (qreal tx, qreal rx, uint32_t fromNodeId, uint32_t toNodeId);
  std::map <uint32_t, QGraphicsLineItem *> m_nodeLines;
  std::vector <QGraphicsLineItem *> m_packetLines;
  std::vector <QGraphicsSimpleTextItem *> m_packetTexts;
  std::vector <QGraphicsSimpleTextItem *> m_nodeIdTexts;

  qreal m_interNodeSpacing;
  qreal m_maxTime;
  QGraphicsProxyWidget * m_infoWidget;

};
}

#endif // PACKETSSCENE_H

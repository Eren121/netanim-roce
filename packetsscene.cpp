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
#include "packetsscene.h"
#include "logqt.h"
#include "animpacket.h"
#include "graphpacket.h"
#include "animatormode.h"
#include "textbubble.h"

namespace netanim {
NS_LOG_COMPONENT_DEFINE ("PacketsScene");

PacketsScene * pPacketsScene = 0;
PacketsScene::PacketsScene ():
  QGraphicsScene (-100, -100, 1024, 1024),
  m_interNodeSpacing (100),
  m_maxTime (0)
{
  m_infoWidget = addWidget (new TextBubble ("Info:", "No data available\nDid you load the XML file?"));
  m_infoWidget->setVisible (true);
  m_infoWidget->setPos (sceneRect ().width ()/2, sceneRect ().height ()/2);
}
PacketsScene *
PacketsScene::getInstance ()
{
  if (!pPacketsScene)
    {
      pPacketsScene = new PacketsScene;
    }
  return pPacketsScene;
}

bool
PacketsScene::setUpNodeLines ()
{
  bool foundNodes = false;
  QRectF r = sceneRect ();
  qreal height = r.bottom () - r.top ();
  qreal borderHeight = 0.01 * height;
  r.setWidth(100 * m_interNodeSpacing);
  setSceneRect(r);
  for (uint32_t nodeId = 0; nodeId < AnimNodeMgr::getInstance ()->getCount () ; ++nodeId)
    {
      foundNodes = true;
      QGraphicsLineItem * lineItem = addLine (m_interNodeSpacing * nodeId, borderHeight, m_interNodeSpacing * nodeId, r.bottom () - borderHeight);
      m_nodeLines[nodeId] = lineItem;
      QGraphicsSimpleTextItem * nodeIdText = new QGraphicsSimpleTextItem (QString::number (nodeId));
      addItem (nodeIdText);
      m_nodeIdTexts.push_back (nodeIdText);
      nodeIdText->setPos (m_interNodeSpacing * nodeId, borderHeight/3);
    }

  return foundNodes;

}


qreal
PacketsScene::timeToY (qreal t)
{
  return t * (1000/m_maxTime);
}

void
PacketsScene::addPacket (qreal tx, qreal rx, uint32_t fromNodeId, uint32_t toNodeId)
{
  qreal fromNodeX = m_interNodeSpacing * fromNodeId;
  qreal toNodeX = m_interNodeSpacing * toNodeId;
  qreal txY = timeToY (tx);
  qreal rxY = timeToY (rx);
  GraphPacket * graphPacket = new GraphPacket (QPointF (fromNodeX, txY), QPointF (toNodeX, rxY));
  addItem (graphPacket);
  //graphPacket->setPos (QPointF (fromNodeX, txY));

}

void
PacketsScene::addPackets ()
{
  bool foundNodes = setUpNodeLines ();
  if (!foundNodes)
    return;
  TimeValue <AnimEvent*> *events = AnimatorMode::getInstance ()->getEvents ();
  m_maxTime = AnimatorMode::getInstance ()->getLastPacketEventTime ();
  m_maxTime = 0.25;
  for (TimeValue<AnimEvent *>::TimeValue_t::const_iterator i = events->Begin ();
      i != events->End ();
      ++i)
    {
      AnimEvent * ev = i->second;
      if (ev->m_type == AnimEvent::PACKET_EVENT)
        {
          AnimPacketEvent * packetEvent = static_cast<AnimPacketEvent *> (ev);
          addPacket (packetEvent->m_fbTx, packetEvent->m_fbRx, packetEvent->m_fromId, packetEvent->m_toId);
        }
    }
  m_infoWidget->setVisible (false);

}


}


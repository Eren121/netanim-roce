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

#include "countertablesscene.h"
#include "statisticsconstants.h"
#include "animnode.h"
#include "animatormode.h"

namespace netanim
{

NS_LOG_COMPONENT_DEFINE ("CounterTablesScene");
CounterTablesScene * pCounterTablesScene = 0;

CounterTablesScene::CounterTablesScene ():QGraphicsScene (100, 0, STATSSCENE_WIDTH_DEFAULT, 3 * STATSSCENE_HEIGHT_DEFAULT)
{
  m_table = new Table ();
  m_tableItem = new QGraphicsProxyWidget;
  m_tableItem->setWidget (m_table);
  addItem (m_tableItem);
}

CounterTablesScene *
CounterTablesScene::getInstance ()
{
  if (!pCounterTablesScene)
    {
      pCounterTablesScene = new CounterTablesScene;
    }
  return pCounterTablesScene;
}


void
CounterTablesScene::setCurrentCounterName (QString name)
{
  m_currentCounterName = name;
  reloadContent ();
}

uint32_t
CounterTablesScene::getIndexForNode (uint32_t nodeId)
{
  int index = 0;
  for (int i = 0; i < m_allowedNodes.count (); ++i)
    {
      if (i == nodeId)
        return index;
      ++index;
    }
  return index;
}

bool
CounterTablesScene::isAllowedNode (uint32_t nodeId)
{
  for (int i = 0; i < m_allowedNodes.count (); ++i)
    {
      if (m_allowedNodes[i] == nodeId)
        return true;
    }
  return false;
}

void
CounterTablesScene::reloadContent (bool force)
{
  Q_UNUSED (force);
  m_table->clear ();
  QStringList headerList;
  headerList << "Time";
  for (QVector <uint32_t>::const_iterator i = m_allowedNodes.begin ();
       i != m_allowedNodes.end ();
       ++i)
    {
      headerList << QString::number (*i);
    }
  m_table->setHeaderList (headerList);

  bool result = false;
  AnimNode::CounterType_t counterType;
  uint32_t counterId = AnimNodeMgr::getInstance ()->getCounterIdForName (m_currentCounterName, result, counterType);
  if (!result)
    return;

  TimeValue <AnimEvent *> * events = AnimatorMode::getInstance ()->getEvents ();
  for (TimeValue<AnimEvent *>::TimeValue_t::const_iterator i = events->Begin ();
      i != events->End ();
      ++i)
    {
      AnimEvent * ev = i->second;
      if (ev->m_type == AnimEvent::UPDATE_NODE_COUNTER_EVENT)
        {
          AnimNodeCounterUpdateEvent * updateEvent = static_cast<AnimNodeCounterUpdateEvent *> (ev);

          if (!isAllowedNode (updateEvent->m_nodeId))
            continue;
          if (updateEvent->m_counterId != counterId)
            continue;
          m_table->incrRowCount ();
          m_table->addCell (0, QString::number (i->first));
          //NS_LOG_DEBUG ("T:" << i->first);
          if (counterType == AnimNode::DOUBLE_COUNTER)
            {
              qreal value = updateEvent->m_counterValue;
              m_table->addCell (getIndexForNode (updateEvent->m_nodeId)+1, QString::number (value));
              //NS_LOG_DEBUG ("Val:" << value);

            }
          else if (counterType == AnimNode::UINT32_COUNTER)
            {
              uint32_t value = static_cast <uint32_t> (updateEvent->m_counterValue);
              m_table->addCell (getIndexForNode (updateEvent->m_nodeId)+1, QString::number (value));
            }

        }
    }
  m_tableItem->setMinimumWidth (sceneRect ().width ());
  m_tableItem->setMinimumHeight (sceneRect ().height ());
  m_table->adjust ();


}

void
CounterTablesScene::setAllowedNodesVector (QVector<uint32_t> allowedNodes)
{
  m_allowedNodes = allowedNodes;
}

}

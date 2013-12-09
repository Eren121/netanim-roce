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

#include "animpropertybrowser.h"
#include "animnode.h"

namespace netanim {

NS_LOG_COMPONENT_DEFINE ("AnimPropertyBroswer");

AnimPropertyBroswer * pAnimPropertyBrowser = 0;

AnimPropertyBroswer::AnimPropertyBroswer ():
  m_currentNodeId (0)
{
  m_vboxLayout = new QVBoxLayout;

  setLayout (m_vboxLayout);

}

AnimPropertyBroswer *
AnimPropertyBroswer::getInstance ()
{
  if (!pAnimPropertyBrowser)
    {
      pAnimPropertyBrowser = new AnimPropertyBroswer;
    }
  return pAnimPropertyBrowser;
}


void
AnimPropertyBroswer::setup ()
{

  m_intManager = new QtIntPropertyManager;
  m_stringManager = new QtStringPropertyManager;
  m_tree = new QtTreePropertyBrowser;
  m_mode = new QComboBox;
  m_nodeIdSelector = new QComboBox;
  m_mode->addItem ("Node");
  m_vboxLayout->addWidget (m_mode);
  uint32_t count = AnimNodeMgr::getInstance ()->getCount ();
  for (uint32_t i = 0; i < count; ++i)
    {
      m_nodeIdSelector->addItem (QString::number (i));
    }
  connect (m_nodeIdSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT (nodeIdSelectorSlot(QString)));
  m_vboxLayout->addWidget (m_nodeIdSelector);
  m_vboxLayout->addWidget (m_tree);

  m_nodeIdProperty = m_intManager->addProperty ("NodeId");
  m_tree->addProperty (m_nodeIdProperty);

  m_nodeDescriptionProperty = m_stringManager->addProperty("NodeDescription");
  m_propertyId[m_nodeDescriptionProperty] = "NodeDescription";
  QtLineEditFactory * lineEditFactory = new QtLineEditFactory;
  m_tree->setFactoryForManager (m_stringManager, lineEditFactory);
  connect (m_stringManager, SIGNAL(valueChanged(QtProperty*,QString)), this, SLOT(valueChangedSlot(QtProperty*,QString)));

  m_tree->addProperty (m_nodeDescriptionProperty);
  AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (0);
  m_stringManager->setValue (m_nodeDescriptionProperty, animNode->getDescription ()->toPlainText ());


}

void
AnimPropertyBroswer::valueChangedSlot(QtProperty * property, QString description)
{
  if (m_nodeDescriptionProperty == property)
    {
      AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
      animNode->setNodeDescription (description);
    }

}

void
AnimPropertyBroswer::nodeIdSelectorSlot (QString newIndex)
{
  NS_LOG_DEBUG (newIndex.toUInt());
  uint32_t nodeId = newIndex.toUInt();
  m_intManager->setValue (m_nodeIdProperty, nodeId);
  AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (nodeId);
  m_stringManager->setValue (m_nodeDescriptionProperty, animNode->getDescription ()->toPlainText());

}


} // namespace netanim

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
#include "animatormode.h"

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
  m_doubleManager = new QtDoublePropertyManager;
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



  m_doubleSpinBoxFactory = new QtDoubleSpinBoxFactory;


  QtGroupPropertyManager * groupManager = new QtGroupPropertyManager;
  QtProperty * nodePosition = groupManager->addProperty ("NodePosition");
  m_nodeXProperty = m_doubleManager->addProperty ("NodeX");
  m_nodeYProperty = m_doubleManager->addProperty ("NodeY");
  nodePosition->addSubProperty (m_nodeXProperty);
  nodePosition->addSubProperty (m_nodeYProperty);
  m_doubleManager->setMinimum (m_nodeXProperty, 0);
  m_doubleManager->setMinimum (m_nodeYProperty, 0);
  m_doubleManager->setValue (m_nodeXProperty, animNode->getX ());
  m_doubleManager->setValue (m_nodeYProperty, animNode->getY ());
  connect (m_doubleManager, SIGNAL(valueChanged(QtProperty*,double)), this, SLOT(valueChangedSlot(QtProperty*,double)));
  m_tree->addProperty (nodePosition);
  m_tree->setFactoryForManager (m_doubleManager, m_doubleSpinBoxFactory);


  m_spinBoxFactory = new QtSpinBoxFactory;
  m_colorManager = new QtColorPropertyManager;
  m_nodeColorProperty = m_colorManager->addProperty ("NodeColor");
  connect(m_colorManager, SIGNAL(valueChanged(QtProperty*,QColor)), this, SLOT(valueChangedSlot(QtProperty*,QColor)));

  m_tree->addProperty (m_nodeColorProperty);
  m_tree->setFactoryForManager (m_colorManager->subIntPropertyManager (), m_spinBoxFactory);
  QColor c = animNode->getColor ();
  m_colorManager->setValue (m_nodeColorProperty, c);


  m_nodeSizeProperty = m_doubleManager->addProperty ("NodeSize");
  m_doubleManager->setValue (m_nodeSizeProperty, animNode->getWidth ());
  m_doubleManager->setMinimum (m_nodeSizeProperty, 0.1);

  m_tree->addProperty (m_nodeSizeProperty);



}

void
AnimPropertyBroswer::valueChangedSlot (QtProperty * property, QColor c)
{
  if (m_nodeColorProperty == property)
    {
      AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
      animNode->setColor (c.red (), c.blue (), c.green (), c.alpha ());
    }
}

void
AnimPropertyBroswer::valueChangedSlot(QtProperty * property, double value)
{
  if (m_nodeXProperty == property)
    {
      AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
      animNode->setX (value);
      qreal x = animNode->getX ();
      qreal y = animNode->getY ();
      animNode->setPos (x, y);
    }
  if (m_nodeYProperty == property)
    {
      AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
      animNode->setY (value);
      qreal x = animNode->getX ();
      qreal y = animNode->getY ();
      animNode->setPos (x, y);
    }
  if (m_nodeSizeProperty == property)
    {
      AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
      AnimatorMode::getInstance ()->setNodeSize (animNode, value);
    }
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

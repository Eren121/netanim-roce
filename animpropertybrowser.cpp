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
#include "animresource.h"

namespace netanim {

NS_LOG_COMPONENT_DEFINE ("AnimPropertyBroswer");

AnimPropertyBroswer * pAnimPropertyBrowser = 0;

AnimPropertyBroswer::AnimPropertyBroswer ():
  m_currentNodeId (0),
  m_intManager (0),
  m_stringManager (0),
  m_doubleManager (0),
  m_colorManager (0),
  m_filePathManager (0),
  m_nodePositionManager (0),
  m_ipv4AddressManager (0),
  m_macAddressManager (0),
  m_staticStringManager (0),
  m_doubleSpinBoxFactory (0),
  m_spinBoxFactory (0),
  m_fileEditFactory (0),
  m_lineEditFactory (0)
{
  m_vboxLayout = new QVBoxLayout;

  setLayout (m_vboxLayout);
  m_tree = new QtTreePropertyBrowser;
  m_mode = new QComboBox;
  m_nodeIdSelector = new QComboBox;
  m_mode->addItem ("Node");
  m_vboxLayout->addWidget (m_mode);

  m_vboxLayout->addWidget (m_nodeIdSelector);
  m_vboxLayout->addWidget (m_tree);

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
AnimPropertyBroswer::postParse ()
{
  uint32_t count = AnimNodeMgr::getInstance ()->getCount ();
  for (uint32_t i = 0; i < count; ++i)
    {
      m_nodeIdSelector->addItem (QString::number (i));
    }
  setup ();
  connect (m_nodeIdSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT (nodeIdSelectorSlot(QString)));

}

void
AnimPropertyBroswer::reset ()
{

  if (m_intManager)
    delete m_intManager;
  if (m_stringManager)
    delete m_stringManager;
  if (m_doubleManager)
    delete m_doubleManager;
  if (m_colorManager)
    delete m_colorManager;
  if (m_filePathManager)
    delete m_filePathManager;
  if (m_nodePositionManager)
    delete m_nodePositionManager;
  if (m_ipv4AddressManager)
    delete m_ipv4AddressManager;
  if (m_macAddressManager)
    delete m_macAddressManager;
  if (m_staticStringManager)
    delete m_staticStringManager;
  m_intManager = 0;
  m_stringManager = 0;
  m_doubleManager = 0;
  m_colorManager = 0;
  m_filePathManager = 0;
  m_nodePositionManager = 0;
  m_ipv4AddressManager = 0;
  m_macAddressManager = 0;
  m_staticStringManager = 0;


  if (m_doubleSpinBoxFactory)
    delete m_doubleSpinBoxFactory;
  if (m_spinBoxFactory)
    delete m_spinBoxFactory;
  if (m_fileEditFactory)
    delete m_fileEditFactory;
  if (m_lineEditFactory)
    delete m_lineEditFactory;

  m_doubleSpinBoxFactory = 0;
  m_spinBoxFactory = 0;
  m_fileEditFactory = 0;
  m_lineEditFactory = 0;

}

void
AnimPropertyBroswer::setup ()
{
  //reset ();
  m_intManager = new QtIntPropertyManager;
  m_stringManager = new QtStringPropertyManager;
  m_doubleManager = new QtDoublePropertyManager;
  m_colorManager = new QtColorPropertyManager;
  m_filePathManager = new FilePathManager;
  m_nodePositionManager = new QtGroupPropertyManager;
  m_ipv4AddressManager = new QtGroupPropertyManager;
  m_macAddressManager = new QtGroupPropertyManager;
  m_staticStringManager = new QtStringPropertyManager;


  m_doubleSpinBoxFactory = new QtDoubleSpinBoxFactory;
  m_spinBoxFactory = new QtSpinBoxFactory;
  m_fileEditFactory = new FileEditFactory;
  m_lineEditFactory = new QtLineEditFactory;


  // Properties

  // Node Id
  m_nodeIdProperty = m_intManager->addProperty ("Node Id");
  m_intManager->setValue (m_nodeIdProperty, m_currentNodeId);
  m_tree->addProperty (m_nodeIdProperty);


  // Node Description
  m_nodeDescriptionProperty = m_stringManager->addProperty ("Node Description");
  m_tree->setFactoryForManager (m_stringManager, m_lineEditFactory);
  connect (m_stringManager, SIGNAL(valueChanged(QtProperty*,QString)), this, SLOT(valueChangedSlot(QtProperty*,QString)));
  m_tree->addProperty (m_nodeDescriptionProperty);
  AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
  m_stringManager->setValue (m_nodeDescriptionProperty, animNode->getDescription ()->toPlainText ());


  // Node Position
  m_nodePositionGroupProperty = m_nodePositionManager->addProperty ("Node Position");
  m_nodeXProperty = m_doubleManager->addProperty ("Node X");
  m_nodeYProperty = m_doubleManager->addProperty ("Node Y");
  m_nodePositionGroupProperty->addSubProperty (m_nodeXProperty);
  m_nodePositionGroupProperty->addSubProperty (m_nodeYProperty);
  m_doubleManager->setMinimum (m_nodeXProperty, 0);
  m_doubleManager->setMinimum (m_nodeYProperty, 0);
  m_doubleManager->setValue (m_nodeXProperty, animNode->getX ());
  m_doubleManager->setValue (m_nodeYProperty, animNode->getY ());
  connect (m_doubleManager, SIGNAL(valueChanged(QtProperty*,double)), this, SLOT(valueChangedSlot(QtProperty*,double)));
  m_tree->addProperty (m_nodePositionGroupProperty);
  m_tree->setFactoryForManager (m_doubleManager, m_doubleSpinBoxFactory);


  // Node Color
  m_nodeColorProperty = m_colorManager->addProperty ("Node Color");
  connect(m_colorManager, SIGNAL(valueChanged(QtProperty*,QColor)), this, SLOT(valueChangedSlot(QtProperty*,QColor)));
  m_tree->addProperty (m_nodeColorProperty);
  m_tree->setFactoryForManager (m_colorManager->subIntPropertyManager (), m_spinBoxFactory);
  QColor c = animNode->getColor ();
  m_colorManager->setValue (m_nodeColorProperty, c);


  // Node Size
  m_nodeSizeProperty = m_doubleManager->addProperty ("Node Size");
  m_doubleManager->setValue (m_nodeSizeProperty, animNode->getWidth ());
  m_doubleManager->setMinimum (m_nodeSizeProperty, 0.1);
  m_tree->addProperty (m_nodeSizeProperty);


  // Node Resource
  int resourceId = animNode->getResourceId ();
  QString resourcePath = "";
  if (resourceId != -1)
    {
      resourcePath = AnimResourceManager::getInstance ()->get (resourceId);
    }
   m_fileEditProperty = m_filePathManager->addProperty ("Node Resource");
   m_filePathManager->setValue (m_fileEditProperty, resourcePath);
   m_tree->addProperty (m_fileEditProperty);
   m_tree->setFactoryForManager (m_filePathManager, m_fileEditFactory);
   connect (m_filePathManager, SIGNAL(valueChanged(QtProperty*,QString)), this, SLOT(valueChangedSlot(QtProperty*,QString)));



   // IPv4 and Mac
   m_ipv4AddressGroupProperty = m_ipv4AddressManager->addProperty ("Ipv4 Addresses");
   m_macAddressGroupProperty = m_macAddressManager->addProperty ("Mac Addresses");
   AnimNode::Ipv4Vector_t ipv4Addresses = animNode->getIpv4Addresses ();
   for (AnimNode::Ipv4Vector_t::const_iterator i = ipv4Addresses.begin ();
        i != ipv4Addresses.end ();
        ++i)
     {
       QtProperty * property = m_staticStringManager->addProperty (*i);
       m_ipv4AddressGroupProperty->addSubProperty (property);
       m_ipv4AddressVectorProperty.push_back (property);
     }
   AnimNode::MacVector_t macAddresses = animNode->getMacAddresses ();
   for (AnimNode::MacVector_t::const_iterator i = macAddresses.begin ();
        i != macAddresses.end ();
        ++i)
    {
      QtProperty * property = m_staticStringManager->addProperty (*i);
      m_macAddressGroupProperty->addSubProperty (property);
      m_macAddressVectorProperty.push_back (property);
    }
   m_tree->addProperty (m_ipv4AddressGroupProperty);
   m_tree->addProperty (m_macAddressGroupProperty);


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
      AnimatorMode::getInstance ()->setNodePos (animNode, x, y);
    }
  if (m_nodeYProperty == property)
    {
      AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
      animNode->setY (value);
      qreal x = animNode->getX ();
      qreal y = animNode->getY ();
      AnimatorMode::getInstance ()->setNodePos (animNode, x, y);

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
  if (m_fileEditProperty == property)
    {
      uint32_t newResourceId = AnimResourceManager::getInstance ()->getNewResourceId ();
      AnimResourceManager::getInstance ()->add (newResourceId, description);
      AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
      animNode->setResource (newResourceId);
    }
}

void
AnimPropertyBroswer::nodeIdSelectorSlot (QString newIndex)
{
  NS_LOG_DEBUG (newIndex.toUInt());
  m_currentNodeId = newIndex.toUInt ();
  m_intManager->setValue (m_nodeIdProperty, m_currentNodeId);
  // Node Id
  m_intManager->setValue (m_nodeIdProperty, m_currentNodeId);


  // Node Description
  AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (m_currentNodeId);
  m_stringManager->setValue (m_nodeDescriptionProperty, animNode->getDescription ()->toPlainText ());


  // Node Position
  m_doubleManager->setValue (m_nodeXProperty, animNode->getX ());
  m_doubleManager->setValue (m_nodeYProperty, animNode->getY ());


  // Node Color
  QColor c = animNode->getColor ();
  m_colorManager->setValue (m_nodeColorProperty, c);


  // Node Size
  m_doubleManager->setValue (m_nodeSizeProperty, animNode->getWidth ());
  m_doubleManager->setMinimum (m_nodeSizeProperty, 0.1);


  // Node Resource
  int resourceId = animNode->getResourceId ();
  QString resourcePath = "";
  if (resourceId != -1)
    {
      resourcePath = AnimResourceManager::getInstance ()->get (resourceId);
    }
   m_filePathManager->setValue (m_fileEditProperty, resourcePath);


   // IPv4 and Mac
   AnimNode::Ipv4Vector_t ipv4Addresses = animNode->getIpv4Addresses ();
   for (AnimPropertyBroswer::QtPropertyVector_t::const_iterator i = m_ipv4AddressVectorProperty.begin ();
        i != m_ipv4AddressVectorProperty.end ();
        ++i)
     {
       QtProperty * property = *i;
       m_ipv4AddressGroupProperty->removeSubProperty (property);
     }
   m_ipv4AddressVectorProperty.clear ();
   for (AnimNode::Ipv4Vector_t::const_iterator i = ipv4Addresses.begin ();
        i != ipv4Addresses.end ();
        ++i)
     {
       QtProperty * property = m_staticStringManager->addProperty (*i);
       m_ipv4AddressGroupProperty->addSubProperty (property);
       m_ipv4AddressVectorProperty.push_back (property);
     }
   AnimNode::MacVector_t macAddresses = animNode->getMacAddresses ();

   for (AnimPropertyBroswer::QtPropertyVector_t::const_iterator i = m_macAddressVectorProperty.begin ();
        i != m_macAddressVectorProperty.end ();
        ++i)
     {
       QtProperty * property = *i;
       m_macAddressGroupProperty->removeSubProperty (property);
     }
   m_macAddressVectorProperty.clear ();

   for (AnimNode::MacVector_t::const_iterator i = macAddresses.begin ();
        i != macAddresses.end ();
        ++i)
    {
      QtProperty * property = m_staticStringManager->addProperty (*i);
      m_macAddressGroupProperty->addSubProperty (property);
      m_macAddressVectorProperty.push_back (property);
    }

}


} // namespace netanim

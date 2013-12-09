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

#ifndef ANIMPROPERTYBROWSER_H
#define ANIMPROPERTYBROWSER_H
#include "common.h"
#include <QtTreePropertyBrowser>
#include <QtIntPropertyManager>
#include <QtSpinBoxFactory>
#include <QtLineEditFactory>
#include <QtDoubleSpinBoxFactory>
#include "filepathmanager.h"
#include "fileeditfactory.h"


namespace netanim {
class AnimPropertyBroswer: public QWidget
{
Q_OBJECT
public:
  static AnimPropertyBroswer * getInstance ();
  void setup ();
private:
  AnimPropertyBroswer();

  QVBoxLayout * m_vboxLayout;
  QtAbstractPropertyBrowser * m_tree;
  QComboBox * m_mode;
  QComboBox * m_nodeIdSelector;

  QtProperty * m_nodeIdProperty;
  QtProperty * m_nodeDescriptionProperty;
  QtProperty * m_nodeXProperty;
  QtProperty * m_nodeYProperty;
  QtProperty * m_nodeColorProperty;
  QtProperty * m_nodeSizeProperty;
  QtProperty * m_fileEditProperty;


  QtIntPropertyManager * m_intManager;
  QtStringPropertyManager * m_stringManager;
  QtDoublePropertyManager * m_doubleManager;
  QtColorPropertyManager * m_colorManager;
  FilePathManager * m_filePathManager;

  QtDoubleSpinBoxFactory * m_doubleSpinBoxFactory;
  QtSpinBoxFactory * m_spinBoxFactory;
  FileEditFactory * m_fileEditFactory;



  uint32_t m_currentNodeId;
  typedef std::map <QtProperty *, QString> PropertyIdMap_t;
  PropertyIdMap_t m_propertyId;
private slots:
  void nodeIdSelectorSlot (QString newIndex);
  void valueChangedSlot (QtProperty*, QString);
  void valueChangedSlot (QtProperty*, double);
  void valueChangedSlot (QtProperty*, QColor);


};

} // namespace netanim
#endif // ANIMPROPERTYBROWSER_H

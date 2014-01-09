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
#ifndef PACKETSMODE_H
#define PACKETSMODE_H

#include "common.h"
#include "mode.h"
namespace netanim {

class PacketsMode: public Mode
{
  Q_OBJECT

public:
  static PacketsMode * getInstance ();
  QWidget * getCentralWidget ();
  QString getTabName ();
  void setFocus (bool focus);

  void setFromTime (qreal fromTime);
  void setToTime (qreal toTime);
  void setAllowedNodes (QString allowedNodesString);
  void showPopup (QString msg);


private:
  PacketsMode ();
  QWidget * m_centralWidget;
  QVBoxLayout * m_vLayout;
  QToolBar * m_mainToolBar;
  QToolButton * m_testButton;
  QToolButton * m_showGridLinesButton;
  QLineEdit * m_fromTimeEdit;
  QLineEdit * m_toTimeEdit;
  QLineEdit * m_allowedNodesEdit;

  QLabel * m_fromTimeLabel;
  QLabel * m_toTimeLabel;
  QLabel * m_allowedNodesLabel;
  QToolButton * m_zoomInButton;
  QToolButton * m_zoomOutButton;


  qreal m_fromTime;
  qreal m_toTime;
  QVector <uint32_t> m_allowedNodes;

  QVector <uint32_t> stringToNodeVector (QString nodeString);

private slots:
  void testSlot ();
  void zoomInSlot ();
  void zoomOutSlot ();
  void fromTimeChangedSlot (QString fromTimeText);
  void toTimeChangedSlot (QString toTimeText);
  void allowedNodesChangedSlot (QString allowedNodes);

};

}

#endif // PACKETSMODE_H

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

#include "packetsmode.h"
#include "packetsview.h"
#include "packetsscene.h"
#include "animatormode.h"

#define TIME_EDIT_WIDTH 150
#define TIME_EDIT_MASK "dddd.ddddddddd"
#define ALLOWED_NODES_WITH 300
#define ALLOWED_NODES "0:1:2:3:4:5:6:7:8:9"

namespace netanim {
PacketsMode * pPacketsMode = 0;

PacketsMode::PacketsMode ():
  m_fromTime (0),
  m_toTime (0)
{
  m_mainToolBar = new QToolBar;
  m_testButton = new QToolButton;
  m_zoomInButton = new QToolButton;
  m_zoomInButton->setText ("Zoom In");  
  connect (m_zoomInButton, SIGNAL(clicked()), this, SLOT(zoomInSlot()));
  m_zoomInButton->setToolTip ("Zoom in");
  m_zoomInButton->setIcon (QIcon (":/resources/animator_zoomin.svg"));


  m_zoomOutButton = new QToolButton;
  m_zoomOutButton->setText ("Zoom Out");
  connect (m_zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOutSlot()));
  m_zoomOutButton->setToolTip ("Zoom Out");
  m_zoomOutButton->setIcon (QIcon (":/resources/animator_zoomout.svg"));


  m_testButton->setText ("test");
  m_showGridLinesButton = new QToolButton;
  m_fromTimeLabel = new QLabel ("From Time");
  m_fromTimeEdit = new QLineEdit;
  QDoubleValidator * doubleValidator = new QDoubleValidator;
  m_fromTimeEdit->setValidator (doubleValidator);
  //m_fromTimeEdit->setInputMask (TIME_EDIT_MASK);
  m_fromTimeEdit->setMaximumWidth (TIME_EDIT_WIDTH);

  m_toTimeLabel = new QLabel ("To Time");
  m_toTimeEdit = new QLineEdit;
  m_toTimeEdit->setValidator (doubleValidator);
  //m_toTimeEdit->setInputMask (TIME_EDIT_MASK);
  m_toTimeEdit->setMaximumWidth (TIME_EDIT_WIDTH);

  m_allowedNodesLabel = new QLabel ("Show Nodes");
  m_allowedNodesEdit = new QLineEdit;
  m_allowedNodesEdit->setMaximumWidth (ALLOWED_NODES_WITH);


  connect (m_testButton, SIGNAL(clicked()), this, SLOT(testSlot()));
  m_mainToolBar->addWidget (m_testButton);
  m_mainToolBar->addWidget (m_zoomInButton);
  m_mainToolBar->addWidget (m_zoomOutButton);
  m_mainToolBar->addSeparator ();
  m_mainToolBar->addWidget (m_showGridLinesButton);
  m_mainToolBar->addWidget (m_fromTimeLabel);
  m_mainToolBar->addWidget (m_fromTimeEdit);
  m_mainToolBar->addWidget (m_toTimeLabel);
  m_mainToolBar->addWidget (m_toTimeEdit);
  m_mainToolBar->addWidget (m_allowedNodesLabel);
  m_mainToolBar->addWidget (m_allowedNodesEdit);


  m_vLayout = new QVBoxLayout;
  m_vLayout->addWidget (m_mainToolBar);
  m_vLayout->addWidget (PacketsView::getInstance ());
  m_centralWidget = new QWidget;
  m_centralWidget->setLayout (m_vLayout);


  setToTime (0);
  setFromTime (0);
  setAllowedNodes (ALLOWED_NODES);
  connect (m_fromTimeEdit, SIGNAL(textChanged(QString)), this, SLOT (fromTimeChangedSlot(QString)));
  connect (m_toTimeEdit, SIGNAL(textChanged(QString)), this, SLOT (toTimeChangedSlot(QString)));
  connect (m_allowedNodesEdit, SIGNAL(textEdited(QString)), this, SLOT (allowedNodesChangedSlot(QString)));

}

QString
PacketsMode::getTabName ()
{
  return "Packets";
}

void
PacketsMode::testSlot ()
{
}


void
PacketsMode::zoomInSlot ()
{
  PacketsView::getInstance ()->zoomIn ();
}


void
PacketsMode::zoomOutSlot ()
{
  PacketsView::getInstance ()->zoomOut ();
}

void
PacketsMode::setFocus (bool focus)
{
  //focus?qDebug (QString ("Animator Focus")):qDebug (QString ("Animator lost Focus"));
  Q_UNUSED (focus);
  if (focus)
    {
      qreal lastPacketTime = AnimatorMode::getInstance ()->getLastPacketEventTime ();
      if (lastPacketTime < 0)
        return;
      uint32_t nodeCount = AnimNodeMgr::getInstance ()->getCount ();
      if (nodeCount == 0)
        return;
      //m_allowedNodes.clear ();

      m_toTime = lastPacketTime;
      setToTime (m_toTime);
      //setAllowedNodes (m_allowedNodes);
      PacketsScene::getInstance ()->redraw(m_fromTime, m_toTime, m_allowedNodes);
    }

}

QWidget *
PacketsMode::getCentralWidget ()
{
  return m_centralWidget;
}
PacketsMode *
PacketsMode::getInstance ()
{
  if (!pPacketsMode)
    {
      pPacketsMode = new PacketsMode;
    }
  return pPacketsMode;
}


void
PacketsMode::setFromTime (qreal fromTime)
{
  m_fromTimeEdit->setText (QString::number (fromTime));
  PacketsScene::getInstance ()->redraw(m_fromTime, m_toTime, m_allowedNodes);

}

void
PacketsMode::setToTime (qreal toTime)
{
  m_toTimeEdit->setText (QString::number (toTime));
  PacketsScene::getInstance ()->redraw(m_fromTime, m_toTime, m_allowedNodes);

}


QVector <uint32_t>
PacketsMode::stringToNodeVector (QString nodeString)
{
  QStringList nodes = nodeString.split (":");
  QVector <uint32_t> v;
  foreach (QString s ,nodes)
    {
      v.push_back (s.toUInt ());
    }
  return v;
}


void
PacketsMode::setAllowedNodes (QString allowedNodesString)
{
  QVector <uint32_t> nodes = stringToNodeVector (allowedNodesString);
  m_allowedNodesEdit->setText (allowedNodesString);
  m_allowedNodes = nodes;
  PacketsScene::getInstance ()->redraw(m_fromTime, m_toTime, m_allowedNodes);

}

void
PacketsMode::showPopup (QString msg)
{
  QMessageBox msgBox;
  msgBox.setText (msg);
  msgBox.exec ();
}

void
PacketsMode::fromTimeChangedSlot (QString fromTimeText)
{
  qreal temp = fromTimeText.toDouble ();
  if (temp > m_toTime)
    {
      showPopup ("From time cannot be greater than To time. Change To time first if necessary");
      setFromTime (0);
      return;
    }
  m_fromTime = temp;
  setFromTime (m_fromTime);

}

void
PacketsMode::toTimeChangedSlot (QString fromTimeText)
{
  qreal temp = fromTimeText.toDouble ();
  if (temp < m_fromTime)
    {
      showPopup ("To time cannot be less than From time");
      setToTime(0);
      return;
    }
  m_toTime = temp;
  setToTime (m_toTime);

}

void
PacketsMode::allowedNodesChangedSlot (QString allowedNodes)
{
  QVector <uint32_t> nodes = stringToNodeVector (allowedNodes);
  if (nodes.empty ())
    {
      showPopup ("unable to parse node list");
      setAllowedNodes (ALLOWED_NODES);
      return;
    }
  setAllowedNodes (allowedNodes);

}


}

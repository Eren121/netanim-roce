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

namespace netanim {
PacketsMode * pPacketsMode = 0;

PacketsMode::PacketsMode ()
{
  m_mainToolBar = new QToolBar;
  m_testButton = new QToolButton;
  m_zoomInButton = new QToolButton;
  m_zoomInButton->setText ("Zoom In");
  connect (m_zoomInButton, SIGNAL(clicked()), this, SLOT(zoomInSlot()));
  m_testButton->setText ("test");
  m_showGridLinesButton = new QToolButton;
  m_gridLineSpacingEdit = new QLineEdit;
  m_gridLineSpacingEdit->setInputMask ("ddd.dddddd");
  connect (m_testButton, SIGNAL(clicked()), this, SLOT(testSlot()));
  m_mainToolBar->addWidget (m_testButton);
  m_mainToolBar->addWidget (m_showGridLinesButton);
  m_mainToolBar->addWidget (m_gridLineSpacingEdit);
  m_mainToolBar->addWidget (m_zoomInButton);

  m_vLayout = new QVBoxLayout;
  m_vLayout->addWidget (m_mainToolBar);
  m_vLayout->addWidget (PacketsView::getInstance ());
  m_centralWidget = new QWidget;
  m_centralWidget->setLayout (m_vLayout);
}

QString
PacketsMode::getTabName ()
{
  return "Packets";
}

void
PacketsMode::testSlot ()
{
  //PacketsView::getInstance ()->fitInView(QRectF (-10,-10, 110, 110));
  PacketsView::getInstance()->test();
  PacketsScene::getInstance ()->test ();
  PacketsView::getInstance()->postParse ();

  //PacketsView::getInstance ()->fitInView(PacketsScene::getInstance ()->sceneRect ());
  //PacketsScene::getInstance()->update();
  //PacketsScene::getInstance()->update();

}


void
PacketsMode::zoomInSlot ()
{
  PacketsView::getInstance ()->zoomIn ();
}

void
PacketsMode::setFocus (bool focus)
{
  //focus?qDebug (QString ("Animator Focus")):qDebug (QString ("Animator lost Focus"));
  Q_UNUSED (focus);
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




}

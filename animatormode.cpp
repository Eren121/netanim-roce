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

#include "common.h"
#include "animatormode.h"
#include "animatorscene.h"
#include "animatorview.h"
#include "animxmlparser.h"
#include "animlink.h"
#include "animresource.h"
#include "statsmode.h"
#include "animpropertybrowser.h"



namespace netanim
{

NS_LOG_COMPONENT_DEFINE ("AnimatorMode");

AnimatorMode * pAnimatorMode = 0;

AnimatorMode::AnimatorMode ():
  m_version (0),
  m_playing (false),
  m_updateRateTimer (0),
  m_currentTime (0),
  m_currentZoomFactor (1),
  m_showWiressCircles (false),
  m_parsedMaxSimulationTime (5000),
  m_oldTimelineValue (0),
  m_simulationCompleted (false),
  m_showPacketMetaInfo (true),
  m_showPackets (true),
  m_fastForwarding (false),
  m_parsingXMLDialog (0),
  m_packetAnimationGroup (0)

{
  init ();
}

void
AnimatorMode::init ()
{
  m_state = APP_INIT;
  initControls ();
  initPropertyBrowser ();
  initToolbars ();
  m_mainSplitter = new QSplitter;
  m_mainSplitter->addWidget (m_verticalToolbar);
  m_mainSplitter->addWidget (AnimatorView::getInstance ());
  m_mainSplitter->addWidget (AnimPropertyBroswer::getInstance ());


  m_vLayout = new QVBoxLayout;
  m_vLayout->setSpacing (0);
  m_vLayout->addWidget (m_topToolBar);
  m_vLayout->addWidget (m_mainSplitter);
  m_vLayout->addWidget (m_bottomToolbar);

  m_centralWidget = new QWidget;
  m_centralWidget->setLayout (m_vLayout);
  setWindowTitle ("NetAnim");
  setControlDefaults ();
  m_state = APP_START;
  m_verticalToolbar->adjustSize ();
}

AnimatorMode *
AnimatorMode::getInstance ()
{
  if (!pAnimatorMode)
    {
      pAnimatorMode = new AnimatorMode;
    }
  return pAnimatorMode;
}

void
AnimatorMode::start ()
{
  clickTraceFileOpenSlot ();

}

void
AnimatorMode::setFocus (bool focus)
{
  //focus?qDebug (QString ("Animator Focus")):qDebug (QString ("Animator lost Focus"));
  Q_UNUSED (focus);
}

void
AnimatorMode::setControlDefaults ()
{
  // Top Horizontal toolbar

  initUpdateRate ();
  m_gridButton->setChecked (false);
  showGridLinesSlot ();
  showBatteryCapacitySlot ();
  m_gridLinesSpinBox->setValue (GRID_LINES_DEFAULT);
  m_nodeSizeComboBox->setCurrentIndex (NODE_SIZE_DEFAULT);
  m_showNodeIdButton->setChecked (true);
  showNodeIdSlot ();

  // Vertical toolbar

  m_showMetaButton->setChecked (true);
  showMetaSlot ();
  m_packetStatsButton->setChecked (false);
  showPacketStatsSlot ();
  m_showWirelessCirclesButton->setChecked (true);
  showWirelessCirclesSlot ();


  // Bottom toolbar/Status bar

  m_parseProgressBar->setVisible (false);


  // Scene elements if any

  //AnimatorScene::getInstance ()->setSceneInfoText ("Please select an XML trace file using the file load button on the top-left corner", true);
  //AnimatorScene::getInstance ()->setSceneInfoText ("Please select an XML trace file using the file load button on the top-left corner", true);


  enableAllToolButtons (false);
  m_fileOpenButton->setEnabled (true);

}


void
AnimatorMode::setToolButtonVector ()
{
  m_toolButtonVector.push_back (m_playButton);
  m_toolButtonVector.push_back (m_updateRateSlider);
  m_toolButtonVector.push_back (m_fastRateLabel);
  m_toolButtonVector.push_back (m_slowRateLabel);
  m_toolButtonVector.push_back (m_gridButton);
  m_toolButtonVector.push_back (m_gridLinesLabel);
  m_toolButtonVector.push_back (m_gridLinesSpinBox);
  m_toolButtonVector.push_back (m_zoomInButton);
  m_toolButtonVector.push_back (m_zoomOutButton);
  m_toolButtonVector.push_back (m_nodeSizeLabel);
  m_toolButtonVector.push_back (m_nodeSizeComboBox);
  m_toolButtonVector.push_back (m_showNodeIdButton);
  m_toolButtonVector.push_back (m_qLcdNumber);
  m_toolButtonVector.push_back (m_blockPacketsButton);
  m_toolButtonVector.push_back (m_resetButton);
  m_toolButtonVector.push_back (m_showIpButton);
  m_toolButtonVector.push_back (m_showMacButton);
  m_toolButtonVector.push_back (m_simulationTimeSlider);
  m_toolButtonVector.push_back (m_showRoutePathButton);
  m_toolButtonVector.push_back (m_addCustomImageButton);
}

void
AnimatorMode::setBottomToolbarWidgets ()
{
  m_bottomToolbar->addWidget (m_bottomStatusLabel);
  m_bottomToolbar->addWidget (m_parseProgressBar);
}

void
AnimatorMode::setVerticalToolbarWidgets ()
{
  m_verticalToolbar->addWidget (m_zoomInButton);
  m_verticalToolbar->addWidget (m_zoomOutButton);
  m_verticalToolbar->addSeparator ();
  m_verticalToolbar->addWidget (m_showNodeIdButton);
  m_verticalToolbar->addSeparator ();
  m_verticalToolbar->addWidget (m_showWirelessCirclesButton);
  m_verticalToolbar->addSeparator ();
  m_verticalToolbar->addWidget (m_packetStatsButton);
  m_verticalToolbar->addWidget (m_nodePositionStatsButton);
  m_verticalToolbar->addWidget (m_blockPacketsButton);
  m_verticalToolbar->addWidget (m_resetButton);
  m_verticalToolbar->addWidget (m_showMetaButton);
  m_verticalToolbar->addWidget (m_batteryCapacityButton);
}

void
AnimatorMode::setTopToolbarWidgets ()
{
  m_topToolBar->addWidget (m_fileOpenButton);
  m_topToolBar->addWidget (m_reloadFileButton);
  m_topToolBar->addSeparator ();
  m_topToolBar->addWidget (m_playButton);
  m_topToolBar->addSeparator ();
  m_topToolBar->addWidget (m_fastRateLabel);
  m_topToolBar->addWidget (m_updateRateSlider);
  m_topToolBar->addWidget (m_slowRateLabel);
  m_topToolBar->addSeparator ();
  //m_topToolBar->addWidget (m_packetPersistenceLabel);
  //m_topToolBar->addWidget (m_packetPersistenceComboBox);
  m_topToolBar->addWidget (m_timelineSliderLabel);
  m_topToolBar->addWidget (m_simulationTimeSlider);
  m_topToolBar->addWidget (m_qLcdNumber);
  m_topToolBar->addSeparator ();
  m_topToolBar->addWidget (m_gridButton);
  m_topToolBar->addWidget (m_gridLinesLabel);
  m_topToolBar->addWidget (m_gridLinesSpinBox);
  m_topToolBar->addSeparator ();
  m_topToolBar->addWidget (m_nodeSizeLabel);
  m_topToolBar->addWidget (m_nodeSizeComboBox);
  m_topToolBar->addSeparator ();
  m_topToolBar->addWidget (m_showIpButton);
  m_topToolBar->addWidget (m_showMacButton);
  //m_topToolBar->addWidget (m_showRoutePathButton);
  m_topToolBar->addWidget (m_testButton);
  m_topToolBar->addWidget (m_addCustomImageButton);
}


void
AnimatorMode::initPropertyBrowser()
{
  //m_propertyBrowser = new QtTreePropertyBrowser;
}

void
AnimatorMode::initControls ()
{
  initLabels ();
  m_fileOpenButton = new QToolButton;
  m_fileOpenButton->setToolTip ("Open XML trace file");
  m_fileOpenButton->setIcon (QIcon (":/resources/animator_fileopen.svg"));
  connect (m_fileOpenButton,SIGNAL (clicked ()), this, SLOT (clickTraceFileOpenSlot ()));


  m_reloadFileButton = new QToolButton;
  m_reloadFileButton->setToolTip ("Reload a file with the same file name as the previous XML");
  m_reloadFileButton->setIcon (QIcon (":/resources/animator_reload.svg"));
  connect (m_reloadFileButton,SIGNAL (clicked ()), this, SLOT (reloadFileSlot ()));


  m_zoomInButton = new QToolButton;
  m_zoomInButton->setToolTip ("Zoom in");
  m_zoomInButton->setIcon (QIcon (":/resources/animator_zoomin.svg"));
  connect (m_zoomInButton, SIGNAL (clicked ()), this, SLOT (clickZoomInSlot ()));


  m_zoomOutButton = new QToolButton;
  m_zoomOutButton->setToolTip ("Zoom out");
  m_zoomOutButton->setIcon (QIcon (":/resources/animator_zoomout.svg"));
  connect (m_zoomOutButton, SIGNAL (clicked ()), this, SLOT (clickZoomOutSlot ()));


  m_gridButton = new QToolButton;
  m_gridButton->setIcon (QIcon (":/resources/animator_grid.svg"));
  m_gridButton->setCheckable (true);
  connect (m_gridButton, SIGNAL (clicked ()), this, SLOT (showGridLinesSlot ()));

  m_gridLinesSpinBox = new QSpinBox;
  m_gridLinesSpinBox->setToolTip ("Set the number of grid lines");
  //m_gridLinesSpinBox->setRange (GRID_LINES_LOW, GRID_LINES_HIGH);
  //m_gridLinesSpinBox->setSingleStep (GRID_LINES_STEP);
  m_gridLinesSpinBox->setRange (GRID_LINES_LOW, GRID_LINES_HIGH);
  m_gridLinesSpinBox->setSingleStep (GRID_LINES_STEP);
  connect (m_gridLinesSpinBox, SIGNAL (valueChanged (int)), this, SLOT (updateGridLinesSlot (int)));

  m_nodeSizeComboBox = new QComboBox;
  m_nodeSizeComboBox->setToolTip ("Node Size");
  QStringList nodeSizes;

  nodeSizes << "0.2"
            << "0.4"
            << "0.5"
            << "0.6"
            << "0.8"
            << "1"
            << "2"
            << "3"
            << "4"
            << "5"
            << "6"
            << "9"
            << "10"
            << "20";
  m_nodeSizeComboBox->addItems (nodeSizes);
  connect (m_nodeSizeComboBox, SIGNAL (currentIndexChanged (QString)), this, SLOT (updateNodeSizeSlot (QString)));

  m_testButton = new QToolButton;
  m_testButton->setText ("T");
  connect (m_testButton, SIGNAL (clicked ()), this, SLOT (testSlot ()));

  m_showIpButton = new QToolButton;
  m_showIpButton->setText ("IP");
  m_showIpButton->setToolTip ("Show IPv4 Addresses");
  m_showIpButton->setCheckable (true);
  connect (m_showIpButton, SIGNAL (clicked ()), this, SLOT (showIpSlot ()));

  m_showMacButton = new QToolButton;
  m_showMacButton->setText ("MAC");
  m_showMacButton->setToolTip ("Show Mac Addresses");
  m_showMacButton->setCheckable (true);
  connect (m_showMacButton, SIGNAL (clicked ()), this, SLOT (showMacSlot ()));

  m_showRoutePathButton = new QToolButton;
  m_showRoutePathButton->setText ("Route-Path");
  m_showRoutePathButton->setToolTip ("Show Route Paths. [EXPERIMENTAL]");
  m_showRoutePathButton->setCheckable (true);
  connect (m_showRoutePathButton, SIGNAL (clicked ()), this, SLOT (showRoutePathSlot ()));


  m_showNodeIdButton = new QToolButton;
  m_showNodeIdButton->setIcon (QIcon (":/resources/animator_nodeid.svg"));
  m_showNodeIdButton->setToolTip ("Show Node Id");
  m_showNodeIdButton->setCheckable (true);
  connect (m_showNodeIdButton, SIGNAL (clicked ()), this, SLOT (showNodeIdSlot ()));


  m_batteryCapacityButton = new QToolButton ();
  m_batteryCapacityButton->setCheckable (true);
  m_batteryCapacityButton->setIcon (QIcon (":/animator_resource/battery_icon_4.png"));
  connect (m_batteryCapacityButton, SIGNAL (clicked ()), this, SLOT (showBatteryCapacitySlot ()));

  m_playButton = new QToolButton;
  m_playButton->setIcon (QIcon (":/resources/animator_play.svg"));
  m_playButton->setToolTip ("Play Animation");
  connect (m_playButton, SIGNAL (clicked ()), this, SLOT (clickPlaySlot ()));


  m_updateRateSlider = new QSlider (Qt::Horizontal);
  m_updateRateSlider->setToolTip ("Animation update interval");
  m_updateRateSlider->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_updateRateSlider, SIGNAL (valueChanged (int)), this, SLOT (updateUpdateRateSlot (int)));
  //m_updateRateSlider->setRange (0, UPDATE_RATE_SLIDER_MAX);
  m_updateRateSlider->setRange (0, UPDATE_RATE_SLIDER_MAX);

  m_simulationTimeSlider = new QSlider (Qt::Horizontal);
  m_simulationTimeSlider->setToolTip ("Set Simulation Time");
  m_simulationTimeSlider->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect (m_simulationTimeSlider, SIGNAL (valueChanged (int)), this, SLOT (updateTimelineSlot (int)));


  m_qLcdNumber = new QLCDNumber;
  m_qLcdNumber->setAutoFillBackground (true);
  m_qLcdNumber->setToolTip ("Current simulation time");
  m_qLcdNumber->setStyleSheet ("QLCDNumber {background:black; color: black;}");
  m_qLcdNumber->setDigitCount (10);

  m_showWirelessCirclesButton = new QToolButton;
  m_showWirelessCirclesButton->setIcon (QIcon (":/resources/animator_wirelesscircles.svg"));
  m_showWirelessCirclesButton->setToolTip ("Toggle Show Wireless Circles Animation");
  m_showWirelessCirclesButton->setCheckable (true);
  connect (m_showWirelessCirclesButton, SIGNAL (clicked ()), this, SLOT (showWirelessCirclesSlot ()));


  m_packetStatsButton = new QToolButton;
  m_packetStatsButton->setIcon (QIcon (":/resources/animator_packetstats.svg"));
  m_packetStatsButton->setToolTip ("Packet filter and statistics");
  connect (m_packetStatsButton, SIGNAL (clicked ()), this, SLOT (showPacketStatsSlot ()));
  m_packetStatsButton->setCheckable (true);


  m_nodePositionStatsButton = new QToolButton;
  m_nodePositionStatsButton->setIcon (QIcon (":/animator_resource/animator_trajectory.svg"));
  m_nodePositionStatsButton->setToolTip ("Node Position statistics");
  connect (m_nodePositionStatsButton, SIGNAL (clicked ()), this, SLOT (showNodePositionStatsSlot ()));
  m_nodePositionStatsButton->setCheckable (true);


  m_blockPacketsButton = new QToolButton;
  m_blockPacketsButton->setIcon (QIcon (":/resources/animator_showpackets.svg"));
  m_blockPacketsButton->setToolTip ("Show packets");
  connect (m_blockPacketsButton, SIGNAL (clicked ()), this, SLOT (showPacketSlot ()));
  m_blockPacketsButton->setCheckable (true);

  m_resetButton = new QToolButton;
  m_resetButton->setText ("R");
  m_resetButton->setToolTip ("Reset Simulation to start");
  connect (m_resetButton, SIGNAL (clicked ()), this, SLOT (clickResetSlot ()));

  m_showMetaButton = new QToolButton;
  m_showMetaButton->setText ("M");
  m_showMetaButton->setCheckable (true);
  m_showMetaButton->setToolTip ("Show Packet meta data");
  connect (m_showMetaButton, SIGNAL (clicked ()), this, SLOT (showMetaSlot ()));

  m_addCustomImageButton = new QToolButton;
  m_addCustomImageButton->setText ("Background");
  m_addCustomImageButton->setToolTip ("Add a custome image to the scene");
  connect (m_addCustomImageButton, SIGNAL (clicked ()), this, SLOT (clickAddCustomImageSlot ()));

  m_parseProgressBar = new QProgressBar;
  //m_animationGroup  = new QParallelAnimationGroup;

  setLabelStyleSheet ();
}

void
AnimatorMode::initLabels ()
{
  m_gridLinesLabel = new QLabel ("Lines");
  m_nodeSizeLabel = new QLabel ("Node Size");
  m_fastRateLabel = new QLabel ("fast");
  m_fastRateLabel->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_fastRateLabel->setFixedWidth (UPDATE_RATE_LABEL_WIDTH);
  m_slowRateLabel = new QLabel ("slow");
  m_slowRateLabel->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_slowRateLabel->setFixedWidth (UPDATE_RATE_LABEL_WIDTH);
  m_timelineSliderLabel = new QLabel ("Sim time");
  m_timelineSliderLabel->setToolTip ("Set current time");
  m_bottomStatusLabel = new QLabel;
}

void
AnimatorMode::initToolbars ()
{
  m_topToolBar = new QToolBar;
  m_verticalToolbar = new QToolBar;
  m_bottomToolbar = new QToolBar;

  QSize iconSize (ICON_WIDTH_DEFAULT, ICON_HEIGHT_DEFAULT);
  m_topToolBar->setIconSize (iconSize);
  m_verticalToolbar->setIconSize (iconSize);
  m_verticalToolbar->setOrientation (Qt::Vertical);
  m_verticalToolbar->setFixedWidth (VERTICAL_TOOLBAR_WIDTH_DEFAULT);

  setTopToolbarWidgets ();
  setVerticalToolbarWidgets ();
  setBottomToolbarWidgets ();
  setToolButtonVector ();
}

QWidget *
AnimatorMode::getCentralWidget ()
{
  return m_centralWidget;
}

void
AnimatorMode::setLabelStyleSheet ()
{
  QString labelStyleSheet = "QLabel {color: black; font: 10px}";
  m_nodeSizeLabel->setStyleSheet (labelStyleSheet);
  m_gridLinesLabel->setStyleSheet (labelStyleSheet);
  m_fastRateLabel->setStyleSheet (labelStyleSheet);
  m_slowRateLabel->setStyleSheet (labelStyleSheet);
  m_timelineSliderLabel->setStyleSheet (labelStyleSheet);
}

void
AnimatorMode::enableAllToolButtons (bool show)
{
  for (int i = 0; i < m_toolButtonVector.size (); ++i)
    {
      m_toolButtonVector[i]->setEnabled (show);
    }
}

QString
AnimatorMode::getTabName ()
{
  return "Animator";
}

void
AnimatorMode::systemReset ()
{
  m_state = SYSTEM_RESET_IN_PROGRESS;
  clickResetSlot ();
  setControlDefaults ();
  AnimatorView::getInstance ()->systemReset ();
  AnimatorScene::getInstance ()->systemReset ();
  for (TimeValue<AnimEvent *>::TimeValue_t::const_iterator i = m_events.Begin ();
      i != m_events.End ();
      ++i)
    {
      delete i->second;
    }
  m_events.systemReset ();
  m_state = SYSTEM_RESET_COMPLETE;
}

void
AnimatorMode::initUpdateRate ()
{
  m_updateRates[0]  = 0.000001;
  m_updateRates[1]  = 0.000002;
  m_updateRates[2]  = 0.000004;
  m_updateRates[3]  = 0.000008;
  m_updateRates[4]  = 0.000016;
  m_updateRates[5]  = 0.000032;
  m_updateRates[6]  = 0.000064;
  m_updateRates[7]  = 0.000125;
  m_updateRates[8]  = 0.000250;
  m_updateRates[9]  = 0.000500;
  m_updateRates[10] = 0.001000;
  m_updateRates[11] = 0.002000;
  m_updateRates[12] = 0.004000;
  m_updateRates[13] = 0.008000;
  m_updateRates[14] = 0.016000;
  m_updateRates[15] = 0.032000;
  m_updateRates[16] = 0.064000;
  m_updateRates[17] = 0.125000;
  m_updateRates[18] = 0.250000;
  m_updateRates[19] = 0.500000;
  m_updateRates[20] = 1.000000;
  m_updateRates[21] = 2.000000;

  m_updateRateSlider->setValue (UPDATE_RATE_SLIDER_DEFAULT);
  if (m_updateRateTimer)
    {
      delete m_updateRateTimer;
    }
  m_updateRateTimer = new QTimer (this);
  //m_updateRateTimer->setInterval (m_updateRates[UPDATE_RATE_SLIDER_DEFAULT] * 1000);
  m_updateRateTimer->setInterval (m_updateRates[UPDATE_RATE_SLIDER_DEFAULT] * 1000);
  connect (m_updateRateTimer, SIGNAL (timeout ()), this, SLOT (updateRateTimeoutSlot ()));
}

qreal
AnimatorMode::nodeSizeStringToValue (QString nodeSize)
{
  if (nodeSize == "0.2")
    return 0.2;
  if (nodeSize == "0.4")
    return 0.4;
  if (nodeSize == "0.5")
    return 0.5;
  if (nodeSize == "0.6")
    return 0.6;
  if (nodeSize == "0.8")
    return 0.8;
  if (nodeSize == "1")
    return 1;
  if (nodeSize == "2")
    return 2;
  if (nodeSize == "3")
    return 3;
  if (nodeSize == "4")
    return 4;
  if (nodeSize == "5")
    return 5;
  if (nodeSize == "6")
    return 6;
  if (nodeSize == "9")
    return 9;
  if (nodeSize == "10")
    return 10;
  if (nodeSize == "20")
    return 20;
  return 1;
}


void
AnimatorMode::externalPauseEvent ()
{
  if (m_state != PLAYING)
    {
      return;
    }
  if (m_playButton->isEnabled ())
    {
      clickPlaySlot ();
    }
}

void
AnimatorMode::showParsingXmlDialog (bool show)
{
  if (!m_parsingXMLDialog)
    {
      m_parsingXMLDialog = new QDialog (this);
      m_parsingXMLDialog->setWindowTitle ("Parsing XML trace file");
      QVBoxLayout * vboxLayout = new QVBoxLayout;
      vboxLayout->addWidget (new QLabel ("Please Wait.Parsing XML trace file"));
      m_parsingXMLDialog->setLayout (vboxLayout);
    }
  if (show)
    {
      m_parsingXMLDialog->show ();
      m_parsingXMLDialog->raise ();
      m_parsingXMLDialog->activateWindow ();
    }
  else
    {
      m_parsingXMLDialog->hide ();
    }
}

void
AnimatorMode::fastForward (qreal t)
{
  while (m_currentTime <t)
    {
      if (m_state == SIMULATION_COMPLETE)
        break;
      //NS_LOG_DEBUG ("Fast Forwarding dispatch");
      dispatchEvents ();
    }
  m_fastForwarding = false;
}


void
AnimatorMode::reset ()
{
  m_updateRateTimer->stop ();
  m_events.rewind ();
  m_events.setCurrentTime (0);
  AnimatorScene::getInstance ()->systemReset ();
  m_currentTime = 0;
}

void
AnimatorMode::setCurrentTime (qreal currentTime)
{
  //NS_LOG_DEBUG ("Setting current time:" << currentTime);
  m_simulationTimeSlider->setValue (currentTime);
  m_qLcdNumber->display (currentTime);
  fflush (stdout);
  reset ();
  fastForward (currentTime);
  if (m_playing)
    m_updateRateTimer->start ();
  m_simulationTimeSlider->setValue (currentTime);
  m_events.setCurrentTime (currentTime);
  m_currentTime = currentTime;

}

void
AnimatorMode::setProgressBarRange (uint64_t rxCount)
{
  m_parseProgressBar->setMaximum (rxCount);
  m_parseProgressBar->setVisible (true);
}

void
AnimatorMode::setMaxSimulationTime (double maxTime)
{
  m_parsedMaxSimulationTime = maxTime;
  m_simulationTimeSlider->setRange (0, m_parsedMaxSimulationTime);
}

void
AnimatorMode::addAnimEvent (qreal t, AnimEvent * event)
{
  m_events.add (t, event);
}

bool
AnimatorMode::parseXMLTraceFile (QString traceFileName)
{
 // NS_LOG_DEBUG ("parsing File:" << traceFileName.toAscii ().data ());
  m_rxCount = 0;
  Animxmlparser parser (traceFileName);
  if (!parser.isFileValid ())
    {
      showPopup ("Trace file is invalid");
      m_fileOpenButton->setEnabled (true);
      return false;
    }
  preParse ();

  showParsingXmlDialog (true);

  m_rxCount = parser.getRxCount ();
  setProgressBarRange (m_rxCount);

  parser.doParse ();
  showParsingXmlDialog (false);
  setMaxSimulationTime (parser.getMaxSimulationTime ());

  postParse ();
  return true;
}

void
AnimatorMode::preParse ()
{
  //AnimatorScene::getInstance ()->preParse ();
  //AnimatorScene::getInstance ()->preParse ();
}



void
AnimatorMode::postParse ()
{
  enableAllToolButtons (true);
  m_showNodeIdButton->setChecked (true);
  showNodeIdSlot ();
  m_gridButton->setChecked (true);
  showGridLinesSlot ();
  AnimatorView::getInstance ()->postParse ();
  //AnimatorScene::getInstance ()->postParse ();
  //AnimatorScene::getInstance ()->setNodeSize (nodeSizeStringToValue (m_nodeSizeComboBox->currentText ()));
  update ();
  m_bottomStatusLabel->setText ("Parsing complete:Click Play");
  m_parseProgressBar->reset ();

  //m_showMetaButton->setChecked (AnimPktMgr::getInstance ()->getMetaInfoSeen ());
  resetBackground ();

  dispatchEvents ();
  m_gridButton->setChecked (false);
  showGridLinesSlot ();
  m_gridButton->setChecked (true);
  showGridLinesSlot ();
  AnimatorView::getInstance ()->postParse ();
  AnimPropertyBroswer::getInstance ()->setup ();

}

void
AnimatorMode::setVersion (double version)
{
  m_version = version;
}

qreal
AnimatorMode::getCurrentNodeSize ()
{
  return nodeSizeStringToValue (m_nodeSizeComboBox->currentText ());
}

QGraphicsPixmapItem *
AnimatorMode::getBackground ()
{
  //return m_background;
  return 0;
}

bool
AnimatorMode::keepAppResponsive ()
{
  if (m_appResponsiveTimer.elapsed () > APP_RESPONSIVE_INTERVAL)
    {
      QApplication::processEvents ();
      m_appResponsiveTimer.restart ();
      return true;
    }
  return false;
}

void
AnimatorMode::resetBackground ()
{
  /*if (!m_background)
      return;
  m_background->setZValue (-1000);
  m_background->setPos (0, 0);
  m_background->setFlags (QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);


  // Modify below as required
  m_background->scale (0.3, 0.3);
  m_background->scale (0.5, 1);*/
}

void
AnimatorMode::setParsingCount (uint64_t parsingCount)
{
  m_bottomStatusLabel->setText ("Parsing Count:" + QString::number (parsingCount) + "/" + QString::number (m_rxCount));
  m_parseProgressBar->setValue (parsingCount);
}

QPropertyAnimation *
AnimatorMode::getButtonAnimation (QToolButton * toolButton)
{
  QPropertyAnimation * propAnimation = new QPropertyAnimation (m_reloadFileButton, "geometry");

  QRectF currentRect = toolButton->geometry ();
  qreal width = currentRect.width ();
  QRectF expandedRect = QRectF (currentRect.left ()- width, currentRect.top () - width,
                               currentRect.right () + width, currentRect.bottom () + width);

  propAnimation->setStartValue (expandedRect);
  propAnimation->setEndValue (currentRect);
  propAnimation->setEasingCurve (QEasingCurve::OutInQuad);
  propAnimation->setDuration (2000);
  return propAnimation;

}

void
AnimatorMode::doSimulationCompleted ()
{
  m_updateRateTimer->stop ();
  m_playButton->setEnabled (false);
  m_simulationTimeSlider->setEnabled (false);
  QApplication::processEvents ();
  //clickResetSlot ();
  m_events.rewind ();
  //setCurrentTime (0);
  m_simulationTimeSlider->setEnabled (false);
  //NS_LOG_DEBUG ("Simulation Completed");
  m_bottomStatusLabel->setText ("Simulation Completed");

  m_buttonAnimationGroup = new QParallelAnimationGroup;
  //m_buttonAnimationGroup->addAnimation (getButtonAnimation (m_fileOpenButton));
  m_buttonAnimationGroup->addAnimation (getButtonAnimation (m_reloadFileButton));

  m_buttonAnimationGroup->start ();

  connect (m_buttonAnimationGroup,
          SIGNAL (finished ()),
          this,
          SLOT (buttonAnimationGroupFinishedSlot ()));

}
bool
AnimatorMode::checkSimulationCompleted ()
{
  return m_state == SIMULATION_COMPLETE;
}

void
AnimatorMode::timerCleanup ()
{
  m_updateRateTimer->stop ();
  setCurrentTime (0);
  m_qLcdNumber->display (0);
  fflush (stdout);
}

void
AnimatorMode::showPopup (QString msg)
{
  if (m_state == APP_INIT)
    {
      return;
    }
  QMessageBox msgBox;
  msgBox.setText (msg);
  msgBox.exec ();
}

void
AnimatorMode::showAnimatorView (bool show)
{
  if (m_state != APP_START)
    {
      enableAllToolButtons (show);
    }
  AnimatorView::getInstance ()->setVisible (show);
}

void
AnimatorMode::showPackets (bool show)
{
  m_blockPacketsButton->setChecked (!show);
  showPacketSlot ();
}


// Slots
void
AnimatorMode::showMetaSlot ()
{
  m_showPacketMetaInfo = m_showMetaButton->isChecked ();

}

void
AnimatorMode::showPacketSlot ()
{
  m_showPackets = !m_blockPacketsButton->isChecked ();
}


void
AnimatorMode::clickResetSlot ()
{
  timerCleanup ();
  m_playing = false;
  m_playButton->setIcon (QIcon (":/resources/animator_play.svg"));
  m_playButton->setToolTip ("Play Animation");
  m_playButton->setEnabled (true);
  AnimatorScene::getInstance ()->purgeAnimatedNodes ();
  AnimatorScene::getInstance ()->purgeAnimatedPackets ();

}

void
AnimatorMode::updateTimelineSlot (int value)
{
  // if (m_animationGroup)
  //     m_animationGroup->stop ();
  if (value == m_oldTimelineValue)
    return;
  m_oldTimelineValue = value;
  m_fastForwarding = true;
  setCurrentTime (value);
  if (m_nodePositionStatsButton->isChecked ())
    {
      if (!m_playing)
        clickPlaySlot ();
    }

  //updateRateTimeoutSlot ();
}

void
AnimatorMode::showNodePositionStatsSlot ()
{

}

void
AnimatorMode::showRoutePathSlot ()
{
}

void
AnimatorMode::showPacketStatsSlot ()
{

}

void
AnimatorMode::showWirelessCirclesSlot ()
{
  m_showWiressCircles = m_showWirelessCirclesButton->isChecked ();
}

void
AnimatorMode::clickZoomInSlot ()
{
  AnimatorScene::getInstance ()->purgeAnimatedPackets ();
  AnimatorView::getInstance ()->setCurrentZoomFactor (++m_currentZoomFactor);

}

void
AnimatorMode::clickZoomOutSlot ()
{
  if (m_currentZoomFactor == 1)
    return;
  AnimatorView::getInstance ()->setCurrentZoomFactor (--m_currentZoomFactor);
  AnimatorScene::getInstance ()->purgeAnimatedPackets ();
  AnimatorScene::getInstance ()->invalidate ();
  AnimatorView::getInstance ()->invalidateScene ();

}


void
AnimatorMode::setSimulationCompleted ()
{
  m_simulationCompleted = true;
  m_state = SIMULATION_COMPLETE;
  doSimulationCompleted ();

}


void
AnimatorMode::purgeAnimatedNodes ()
{

}

void
AnimatorMode::updateRateTimeoutSlot ()
{
  AnimatorScene::getInstance ()->invalidate ();
  m_updateRateTimer->stop ();
  if (m_state == SIMULATION_COMPLETE)
    return;
  if (m_playing)
    {
      dispatchEvents ();
      m_simulationTimeSlider->setValue (m_currentTime);
      m_qLcdNumber->display (m_currentTime);
      keepAppResponsive ();
      m_updateRateTimer->start ();
    }
}

void
AnimatorMode::updateUpdateRateSlot (int value)
{
  //if (m_animationGroup)
  //   m_animationGroup->stop ();
  m_currentUpdateRate = m_updateRates[value];
  if (m_updateRateTimer)
    {
      m_updateRateTimer->setInterval (m_currentUpdateRate * 1000);
    }
}

void
AnimatorMode::clickAddCustomImageSlot ()
{
  /*     QFileDialog fileDialog;
       fileDialog.setFileMode (QFileDialog::ExistingFiles);
       QString traceFileName = "";
       if (fileDialog.exec ())
       {
           traceFileName = fileDialog.selectedFiles ().at (0);
           //qDebug ((traceFileName));
           if (traceFileName != "")
           {
               QPixmap pixmap (traceFileName);
               m_background = new QGraphicsPixmapItem (pixmap);
               AnimatorScene::getInstance ()->addItem (m_background);
               resetBackground ();
           }
       }
       */

}


void
AnimatorMode::reloadFileSlot ()
{
  if (m_traceFileName == "")
    {
      showPopup ("FileName unknown");
      return;
    }

  StatsMode::getInstance ()->systemReset ();
  systemReset ();
  parseXMLTraceFile (m_traceFileName);
  StatsMode::getInstance ()->systemReset ();

  QApplication::processEvents ();


}
void
AnimatorMode::clickTraceFileOpenSlot ()
{
  StatsMode::getInstance ()->systemReset ();
  systemReset ();
  QFileDialog fileDialog;
  fileDialog.setFileMode (QFileDialog::ExistingFiles);

  QString traceFileName = "";
  m_traceFileName = "";
  if (fileDialog.exec ())
    {
      traceFileName = fileDialog.selectedFiles ().at (0);
      if (traceFileName != "")
        {
          m_traceFileName = traceFileName;
          if (parseXMLTraceFile (traceFileName))
            m_fileOpenButton->setEnabled (true);
        }
    }
  StatsMode::getInstance ()->systemReset ();
  QApplication::processEvents ();
}


void
AnimatorMode::clickPlaySlot ()
{
  m_playing = !m_playing;
  if (m_playing)
    {
      if (m_state == SIMULATION_COMPLETE)
        {
          reset ();
        }
      m_state = PLAYING;
      m_bottomStatusLabel->setText ("Playing");
      if (m_simulationCompleted)
        {
          //AnimatorScene::getInstance ()->softReset ();
          m_simulationCompleted = false;
        }
      m_appResponsiveTimer.restart ();
      m_playButton->setIcon (QIcon (":/resources/animator_pause.svg"));
      m_playButton->setToolTip ("Pause Animation");
      m_updateRateTimer->start ();

    }
  else
    {
      m_state = PAUSING;
      m_bottomStatusLabel->setText ("Not Playing");
      m_playButton->setIcon (QIcon (":/resources/animator_play.svg"));
      m_playButton->setToolTip ("Play Animation");
      m_updateRateTimer->stop ();
    }
}

void
AnimatorMode::dispatchEvents ()
{
  m_updateRateSlider->setEnabled (false);
  m_simulationTimeSlider->setEnabled (false);
  //m_zoomInButton->setEnabled (false);
  //m_zoomOutButton->setEnabled (false);

  TimeValue<AnimEvent*>::TimeValueResult_t result;
  TimeValue<AnimEvent*>::TimeValueIteratorPair_t pp = m_events.getNext (result);
  //NS_LOG_DEBUG ("Now:" << pp.first->first);
  if (result == m_events.GOOD)
    {
      //setCurrentTime (pp.first->first);
      m_currentTime = pp.first->first;
      if (m_currentTime > 0)
        {
          m_simulationTimeSlider->setEnabled (true);
        }
      QVector <AnimPacket *> packetsToAnimate;
      for (TimeValue<AnimEvent*>::TimeValue_t::const_iterator j = pp.first;
          j != pp.second;
          ++j)
        {
          //NS_LOG_DEBUG ("fbTx:" << j->first);
          AnimEvent * ev = j->second;
          AnimatorScene::getInstance ()->purgeAnimatedPackets ();

          switch (ev->m_type)
            {
            case AnimEvent::ADD_NODE_EVENT:
            {
              AnimNodeAddEvent * addEvent = static_cast<AnimNodeAddEvent *> (ev);
              AnimNode * animNode = AnimNodeMgr::getInstance ()->add (addEvent->m_nodeId,
                                    addEvent->m_x,
                                    addEvent->m_y,
                                    addEvent->m_nodeDescription);
              AnimatorScene::getInstance ()->addNode (animNode);
              AnimatorView::getInstance ()->postParse ();
              break;
            }
            case AnimEvent::PACKET_EVENT:
            {
              if (m_fastForwarding || ! (m_showPackets))
                continue;
              AnimPacketEvent * packetEvent = static_cast<AnimPacketEvent *> (j->second);
              AnimPacket * animPacket = AnimPacketMgr::getInstance ()->add (packetEvent->m_fromId,
                                        packetEvent->m_toId,
                                        packetEvent->m_fbTx,
                                        packetEvent->m_fbRx,
                                        packetEvent->m_isWPacket,
                                        packetEvent->m_metaInfo,
                                        m_showPacketMetaInfo);
              packetsToAnimate.push_back (animPacket);
              break;

            }
            case AnimEvent::UPDATE_NODE_POS_EVENT:
            {
              //NS_LOG_DEBUG ("Node Update POs");
              AnimNodePositionUpdateEvent * ev = static_cast<AnimNodePositionUpdateEvent *> (j->second);
              AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (ev->m_nodeId);
              animNode->setX (ev->m_x);
              animNode->setY (ev->m_y);
              animNode->setPos (animNode->getX (), animNode->getY ());
              animNode->getDescription ()->setPos (animNode->sceneBoundingRect ().bottomRight ());
              LinkManager::getInstance ()->repairLinks (animNode->getNodeId ());

              break;
            }
            case AnimEvent::UPDATE_NODE_COLOR_EVENT:
            {
              AnimNodeColorUpdateEvent * ev = static_cast<AnimNodeColorUpdateEvent *> (j->second);
              AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (ev->m_nodeId);
              animNode->setColor (ev->m_r, ev->m_g, ev->m_b);
              break;

            }
            case AnimEvent::UPDATE_NODE_DESCRIPTION_EVENT:
            {
              AnimNodeDescriptionUpdateEvent * ev = static_cast<AnimNodeDescriptionUpdateEvent *> (j->second);
              AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (ev->m_nodeId);
              animNode->setNodeDescription (ev->m_description);
              break;
            }
            case AnimEvent::UPDATE_NODE_SIZE_EVENT:
            {
              AnimNodeSizeUpdateEvent * ev = static_cast<AnimNodeSizeUpdateEvent *> (j->second);
              AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (ev->m_nodeId);
              animNode->setSize (ev->m_width, ev->m_height);
              animNode->getDescription ()->setPos (animNode->sceneBoundingRect ().bottomRight ());
              LinkManager::getInstance ()->repairLinks (animNode->getNodeId ());
              break;
            }
            case AnimEvent::UPDATE_NODE_IMAGE_EVENT:
            {
              AnimNodeImageUpdateEvent * ev = static_cast<AnimNodeImageUpdateEvent *> (j->second);
              AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (ev->m_nodeId);
              uint32_t resourceId = ev->m_resourceId;
              QString resourcePath = AnimResourceManager::getInstance ()->get (resourceId);
              //NS_LOG_DEBUG ("Res:" << resourcePath.toAscii ().data ());
              QPixmap pix (resourcePath, "png");
              animNode->setPixmap (pix);
              LinkManager::getInstance ()->repairLinks (animNode->getNodeId ());
              break;

            }
            case AnimEvent::ADD_LINK_EVENT:
            {

              AnimLinkAddEvent * ev = static_cast<AnimLinkAddEvent *> (j->second);
              AnimLink * animLink = LinkManager::getInstance ()->addLink (ev->m_fromNodeId, ev->m_toNodeId,
                                    ev->m_fromNodeDescription, ev->m_toNodeDescription,
                                    ev->m_linkDescription,
                                    ev->m_p2p);
              AnimatorScene::getInstance ()->addLink (animLink);
            }
            case AnimEvent::UPDATE_LINK_EVENT:
            {
              AnimLinkUpdateEvent * ev = static_cast<AnimLinkUpdateEvent *> (j->second);
              LinkManager::getInstance ()->updateLink (ev->m_fromNodeId, ev->m_toNodeId, ev->m_linkDescription);
              break;
            }


            } //switch
        } // for loop
      m_packetAnimationGroup  = new QParallelAnimationGroup;
      for (QVector <AnimPacket *>::const_iterator i = packetsToAnimate.begin ();
           i != packetsToAnimate.end ();
           ++i)
        {
          AnimPacket * animPacket = *i;
          AnimatorScene::getInstance ()->addPacket (animPacket);
          animPacket->update (m_currentTime);
          animPacket->setVisible (true);
          animPacket->setPos (animPacket->getHead ());

          if (animPacket->getIsWPacket () && m_showWiressCircles)
            {
              uint32_t fromNodeId = animPacket->getFromNodeId ();
              uint32_t toNodeId = animPacket->getToNodeId ();

              QPointF fromNodePos = AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getCenter ();
              QPointF toNodePos = AnimNodeMgr::getInstance ()->getNode (toNodeId)->getCenter ();
              AnimWirelessCircles * pAnimWirelessCircle = new AnimWirelessCircles;
              AnimatorScene::getInstance ()->addWirelessCircle (pAnimWirelessCircle);

              QPropertyAnimation * wirelessAnimation = new QPropertyAnimation (pAnimWirelessCircle, "rect");
              qreal duration = m_currentUpdateRate * 1000;
              wirelessAnimation->setDuration (duration);
              if (m_fastForwarding)
                duration = 0;
              wirelessAnimation->setStartValue (QRectF (fromNodePos, fromNodePos));
              QLineF l (fromNodePos, toNodePos);
              qreal length = l.length ();
              qreal hypotenuse = length;// sqrt ((length * length) *2);
              QPointF topLeft = QPointF (fromNodePos.x () - hypotenuse, fromNodePos.y () - hypotenuse);
              QPointF bottomRight = QPointF (fromNodePos.x () + hypotenuse, fromNodePos.y () + hypotenuse);
              wirelessAnimation->setEndValue (QRectF (topLeft, bottomRight));
              m_packetAnimationGroup->addAnimation (wirelessAnimation);

            }



          QPropertyAnimation * propertyAnimation = new QPropertyAnimation (animPacket, "pos");
          qreal duration = m_currentUpdateRate * 1000;
          if (m_fastForwarding)
            duration = 0;
          propertyAnimation->setDuration (duration);
          propertyAnimation->setStartValue (animPacket->getFromPos ());
          propertyAnimation->setEndValue (animPacket->getToPos ());
          //propAnimation->start ();
          // m_animationGroup->addAnimation (propertyAnimation);

          //AnimatorScene::getInstance ()->update ();
        }
      //NS_LOG_DEBUG ("Animation duration:" << animationGroup->duration ());

      //m_animationGroup->start (QPropertyAnimation::DeleteWhenStopped);
      m_packetAnimationGroup->start ();

      connect (m_packetAnimationGroup,
              SIGNAL (finished ()),
              this,
              SLOT (packetAnimationGroupFinishedSlot ()));

      //delete animationGroup;
      //AnimatorScene::getInstance ()->setShowInterfaceTexts (true, true);
      m_updateRateSlider->setEnabled (true);
      m_simulationTimeSlider->setEnabled (true);
    } // if result == good
  else
    {
      //showPopup ("Result : BAD");
      //NS_LOG_DEBUG ("Set Simulation completed");
      setSimulationCompleted ();
    }




}

void
AnimatorMode::packetAnimationGroupFinishedSlot ()
{
  //NS_LOG_DEBUG ("animationGroupStateChangedSlot");
  //if (newState != QAbstractAnimation::Stopped)
  //    return;
  m_packetAnimationGroup->deleteLater ();
  //m_updateRateTimer->start ();
  //m_updateRateSlider->setEnabled (true);
  //m_simulationTimeSlider->setEnabled (true);
  //m_zoomInButton->setEnabled (true);
  //m_zoomOutButton->setEnabled (true);
}


void
AnimatorMode::buttonAnimationGroupFinishedSlot ()
{
  if (m_state == SIMULATION_COMPLETE)
    {
      m_buttonAnimationGroup->start ();
    }
  else
    {
      m_buttonAnimationGroup->deleteLater ();
    }

}

void
AnimatorMode::testSlot ()
{
  //AnimatorScene::getInstance ()->test ();

  //AnimatorScene::getInstance ()->test ();
  static qreal t = 0.659;
  m_qLcdNumber->display (t);
  //displayPacket (t);
  dispatchEvents ();
  t += 0.00005;
}

void
AnimatorMode::setNodeSize (AnimNode *animNode, qreal size)
{
  animNode->setSize (size, size);
  animNode->getDescription ()->setPos (animNode->sceneBoundingRect ().bottomRight ());
  LinkManager::getInstance ()->repairLinks (animNode->getNodeId ());

}

void
AnimatorMode::updateNodeSizeSlot (QString value)
{
  qreal size = nodeSizeStringToValue (value);
  AnimNodeMgr::getInstance ()->setSize (size, size);
  uint32_t nodeCount = AnimNodeMgr::getInstance ()->getCount ();
  for (uint32_t i = 0; i < nodeCount; ++i)
    {
      AnimNode * animNode = AnimNodeMgr::getInstance ()->getNode (i);
      setNodeSize (animNode, size);
    }

}

void
AnimatorMode::showNodeIdSlot ()
{
  AnimNodeMgr::getInstance ()->showNodeId (m_showNodeIdButton->isChecked ());
  if (m_showNodeIdButton->isChecked ())
    {
      m_showNodeIdButton->setToolTip ("Don't show Node Id");
    }
  else
    {
      m_showNodeIdButton->setToolTip ("Show Node Id");
    }
}

void
AnimatorMode::showBatteryCapacitySlot ()
{
  if (m_batteryCapacityButton->isChecked ())
    {
      m_batteryCapacityButton->setToolTip ("Don't show remaining capacity");
    }
  else
    {
      m_batteryCapacityButton->setToolTip ("Show remaining capacity");
    }
}


void
AnimatorMode::showIpSlot ()
{
  AnimatorScene::getInstance ()->setShowInterfaceTexts (m_showIpButton->isChecked (), m_showMacButton->isChecked ());

}

void
AnimatorMode::showMacSlot ()
{
  AnimatorScene::getInstance ()->setShowInterfaceTexts (m_showIpButton->isChecked (), m_showMacButton->isChecked ());

}

void
AnimatorMode::showGridLinesSlot ()
{

  if (m_gridButton->isChecked ())
    {
      AnimatorScene::getInstance ()->addGrid ();
      m_gridButton->setToolTip ("Turn OFF Grid");
    }
  else
    {
      AnimatorScene::getInstance ()->resetGrid ();
      m_gridButton->setToolTip ("Turn ON Grid");
    }
}



void
AnimatorMode::updateGridLinesSlot (int value)
{
  AnimatorScene::getInstance ()->setGridLinesCount (value);

}



} // namespace netanim


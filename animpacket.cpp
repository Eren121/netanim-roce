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
#include <iostream>
#include <math.h>
#include <QPointF>
#include <QPainter>
#include <QPainterPath>
#include <QStaticText>
#include <QTextItem>
#include "animpacket.h"
#include "animnode.h"
#include "animatorview.h"
#include "log.h"
#include "logqt.h"


#define PI 3.14159265
NS_LOG_COMPONENT_DEFINE("AnimPacket");

namespace netanim {
AnimPacketMgr * pAnimPacketMgr = 0;

AnimPacket::AnimPacket (uint32_t fromNodeId,
                        uint32_t toNodeId,
                        qreal firstBitTx,
                        qreal firstBitRx,
                        bool isWPacket,
                        QString metaInfo,
                        bool showMetaInfo):
    AnimEvent(PACKET_EVENT),
    m_fromNodeId (fromNodeId),
    m_toNodeId (toNodeId),
    m_firstBitTx (firstBitTx),
    m_firstBitRx (firstBitRx),
    m_isWPacket (isWPacket),
    m_infoText(0)
{
  m_fromPos = AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getCenter ();
  //m_fromPos = QPointF(AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getX(), AnimNodeMgr::getInstance ()->getNode (fromNodeId)->getY());
  //m_toPos = QPointF(AnimNodeMgr::getInstance ()->getNode (toNodeId)->getX(), AnimNodeMgr::getInstance ()->getNode (toNodeId)->getY());

  m_toPos = AnimNodeMgr::getInstance ()->getNode (toNodeId)->getCenter ();
  //NS_LOG_DEBUG ("FromPos:" << m_fromPos);
  //NS_LOG_DEBUG ("ToPos:" << m_toPos);
  m_line = QLineF (m_fromPos, m_toPos);
  qreal propDelay = m_firstBitRx - m_firstBitTx;
  m_velocity = m_line.length ()/propDelay;
  m_cos = cos ((360 - m_line.angle ()) * PI/180);
  m_sin = sin ((360 - m_line.angle ()) * PI/180);
  setVisible(false);
  setZValue(ANIMPACKET_ZVAVLUE);

      m_infoText = new QGraphicsSimpleTextItem (this);
      if(showMetaInfo)
      {
      m_infoText->setText("p");
      m_infoText->setFlag(QGraphicsItem::ItemIgnoresTransformations);


      qreal textAngle = m_line.angle ();
      if(textAngle < 90)
      {
          textAngle = 360-textAngle;
      }
      else if (textAngle > 270)
      {
          textAngle = 360-textAngle;
      }
      else
      {
        textAngle = 180-textAngle;
      }
      m_infoText->rotate(textAngle);
      m_infoText->setText(getShortMeta(metaInfo));
  }

}

AnimPacket::~AnimPacket()
{
    if(m_infoText)
    {
        delete m_infoText;
    }
}

QString
AnimPacket::getShortMeta(QString metaInfo)
{
    bool result = false;
    QString metaInfoString = metaInfo.toAscii().data();
    AodvInfo aodvInfo = parseAodv(metaInfoString, result);
    if (result)
    {
        return aodvInfo.toShortString();
    }


    result = false;
    OlsrInfo olsrInfo = parseOlsr(metaInfoString, result);
    if(result)
    {
        return olsrInfo.toShortString();
    }


    result = false;
    DsdvInfo dsdvInfo = parseDsdv(metaInfoString, result);
    if(result)
    {
        return dsdvInfo.toShortString();
    }



    result = false;
    TcpInfo tcpInfo = parseTcp(metaInfoString, result);
    if(result)
    {
        return tcpInfo.toShortString();
    }



    result = false;
    UdpInfo udpInfo = parseUdp(metaInfoString, result);
    if(result)
    {
        return udpInfo.toShortString();
    }



    result = false;
    ArpInfo arpInfo = parseArp(metaInfoString, result);
    if(result)
    {
        return arpInfo.toShortString();
    }




    result = false;
    IcmpInfo icmpInfo = parseIcmp(metaInfoString, result);
    if(result)
    {
        return icmpInfo.toShortString();

    }


    result = false;
    Ipv4Info ipv4Info = parseIpv4(metaInfoString, result);
    if(result)
    {
        return ipv4Info.toShortString();
    }


    result = false;
    WifiMacInfo wifiMacInfo = parseWifi(metaInfoString, result);
    if(result)
    {
        return wifiMacInfo.toShortString();
    }


    result = false;
    PppInfo pppInfo = parsePpp(metaInfoString, result);
    if(result)
    {
        return pppInfo.toShortString();
    }

    result = false;
    EthernetInfo ethernetInfo = parseEthernet(metaInfoString, result);
    if(result)
    {
        return ethernetInfo.toShortString();
    }
    return "";

}

uint32_t
AnimPacket::getFromNodeId ()
{
  return m_fromNodeId;
}

uint32_t
AnimPacket::getToNodeId ()
{
  return m_toNodeId;
}

qreal
AnimPacket::getFirstBitTx ()
{
  return m_firstBitTx;
}

qreal
AnimPacket::getFirstBitRx ()
{
  return m_firstBitRx;
}


bool
AnimPacket::getIsWPacket()
{
    return m_isWPacket;
}

QGraphicsSimpleTextItem *
AnimPacket::getInfoTextItem()
{
    return m_infoText;
}



PppInfo
AnimPacket::parsePpp(QString metaInfo, bool & result)
{
    PppInfo pppInfo;
    QRegExp rx("ns3::PppHeader.*");
    int pos = 0;
    if((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = true;
        return pppInfo;
    }
    result = true;
    return pppInfo;

}


ArpInfo
AnimPacket::parseArp(QString metaInfo, bool & result)
{
    ArpInfo arpInfo;

    QRegExp rx("ns3::ArpHeader\\s+\\((request|reply) source mac: ..-..-(..:..:..:..:..:..) source ipv4: (\\S+) (?:dest mac: ..-..-)?(..:..:..:..:..:.. )?dest ipv4: (\\S+)\\)");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return arpInfo;
    }
    arpInfo.type = rx.cap(1).toAscii().data();
    arpInfo.sourceMac = rx.cap(2).toAscii().data();
    arpInfo.sourceIpv4 = rx.cap(3).toAscii().data();
    if( QString(rx.cap(4).toAscii().data()) != "")
    arpInfo.destMac = rx.cap(4).toAscii().data();
    arpInfo.destIpv4  = rx.cap(5).toAscii().data();
    result = true;
    return arpInfo;
    /*qDebug (" Type:" + arpInfo->type +
            " SMac:" + arpInfo->sourceMac +
            " SIp:"  + arpInfo->sourceIpv4 +
            " DMac:" + arpInfo->destMac +
            " DIp:"  + arpInfo->destIpv4);*/


}

EthernetInfo
AnimPacket::parseEthernet(QString metaInfo, bool & result)
{
    EthernetInfo ethernetInfo;
    QRegExp rx("ns3::EthernetHeader \\( length/type\\S+ source=(..:..:..:..:..:..), destination=(..:..:..:..:..:..)\\)");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return ethernetInfo;
    }
    ethernetInfo.sourceMac = rx.cap(1).toAscii().data();
    ethernetInfo.destMac = rx.cap(2).toAscii().data();
    result = true;
    return ethernetInfo;
}


IcmpInfo
AnimPacket::parseIcmp(QString metaInfo, bool & result)
{
    IcmpInfo icmpInfo;

    QRegExp rx("ns3::Icmpv4Header \\(type=(.*), code=([^\\)]*)");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return icmpInfo;
    }
    icmpInfo.type = rx.cap(1).toAscii().data();
    icmpInfo.code = rx.cap(2).toAscii().data();
    result = true;
    return icmpInfo;

}

UdpInfo
AnimPacket::parseUdp(QString metaInfo, bool & result)
{
    UdpInfo udpInfo;

    QRegExp rx("ns3::UdpHeader \\(length: (\\S+) (\\S+) > (\\S+)\\)");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return udpInfo;
    }
    udpInfo.length = rx.cap(1).toAscii().data();
    udpInfo.SPort = rx.cap(2).toAscii().data();
    udpInfo.DPort = rx.cap(3).toAscii().data();
    result = true;
    return udpInfo;
}

Ipv4Info
AnimPacket::parseIpv4(QString metaInfo, bool & result)
{
    Ipv4Info ipv4Info;

    QRegExp rx("ns3::Ipv4Header \\(tos (\\S+) DSCP (\\S+) ECN (\\S+) ttl (\\d+) id (\\d+) protocol (\\d+) .* length: (\\d+) (\\S+) > (\\S+)\\)");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return ipv4Info;
    }
    ipv4Info.tos = rx.cap(1).toAscii().data();
    ipv4Info.Dscp = rx.cap(2).toAscii().data();
    ipv4Info.Ecn = rx.cap(3).toAscii().data();
    ipv4Info.Ttl = rx.cap(4).toAscii().data();
    ipv4Info.Id = rx.cap(5).toAscii().data();
    ipv4Info.protocol = rx.cap(6).toAscii().data();
    ipv4Info.length = rx.cap(7).toAscii().data();
    ipv4Info.SrcIp = rx.cap(8).toAscii().data();
    ipv4Info.DstIp = rx.cap(9).toAscii().data();
    result = true;
    return ipv4Info;
}

TcpInfo
AnimPacket::parseTcp(QString metaInfo, bool & result)
{
    TcpInfo tcpInfo;

    QRegExp rx("ns3::TcpHeader \\((\\S+) > (\\S+) \\[([^\\]]*)\\] Seq=(\\S+) Ack=(\\S+) Win=(\\S+)\\)");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return tcpInfo;
    }
    tcpInfo.SPort = rx.cap(1).toAscii().data();
    tcpInfo.DPort = rx.cap(2).toAscii().data();
    tcpInfo.flags = rx.cap(3).toAscii().data();
    tcpInfo.seq = rx.cap(4).toAscii().data();
    tcpInfo.ack = rx.cap(5).toAscii().data();
    tcpInfo.window = rx.cap(6).toAscii().data();
    result = true;
    return tcpInfo;
}

WifiMacInfo
AnimPacket::parseWifi(QString metaInfo, bool & result)
{
    QRegExp rxCTL_ACK("ns3::WifiMacHeader \\(CTL_ACK .*RA=(..:..:..:..:..:..)");
    WifiMacInfo wifiMacInfo;
    int pos = 0;
    if ((pos = rxCTL_ACK.indexIn(metaInfo)) != -1)
    {
        wifiMacInfo.type = "CTL_ACK";
        wifiMacInfo.Ra = rxCTL_ACK.cap(1).toAscii().data();
        result = true;
       return wifiMacInfo;

    }
    QRegExp rxCTL_RTS("ns3::WifiMacHeader \\(CTL_RTS .*RA=(..:..:..:..:..:..), TA=(..:..:..:..:..:..)");
    pos = 0;
    if ((pos = rxCTL_RTS.indexIn(metaInfo)) != -1)
    {
        wifiMacInfo.type = "CTL_RTS";
        wifiMacInfo.Ra = rxCTL_RTS.cap(1).toAscii().data();
        wifiMacInfo.Sa = rxCTL_RTS.cap(2).toAscii().data();
        result = true;
       return wifiMacInfo;

    }

    QRegExp rxCTL_CTS("ns3::WifiMacHeader \\(CTL_CTS .*RA=(..:..:..:..:..:..)");
    pos = 0;
    if ((pos = rxCTL_CTS.indexIn(metaInfo)) != -1)
    {
        wifiMacInfo.type = "CTL_CTS";
        wifiMacInfo.Ra = rxCTL_CTS.cap(1).toAscii().data();
        result = true;
        return wifiMacInfo;

    }

    QRegExp rx("ns3::WifiMacHeader \\((\\S+) ToDS=(0|1), FromDS=(0|1), .*DA=(..:..:..:..:..:..), SA=(..:..:..:..:..:..), BSSID=(..:..:..:..:..:..)");
    pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return wifiMacInfo;
    }
    wifiMacInfo.type = rx.cap(1).toAscii().data();
    wifiMacInfo.toDs = rx.cap(2).toAscii().data();
    wifiMacInfo.fromDs = rx.cap(3).toAscii().data();
    wifiMacInfo.Da = rx.cap(4).toAscii().data();
    wifiMacInfo.Sa = rx.cap(5).toAscii().data();
    wifiMacInfo.Bssid = rx.cap(6).toAscii().data();

    if(wifiMacInfo.type == "MGT_ASSOCIATION_REQUEST")
    {
        QRegExp rx("ns3::MgtAssocRequestHeader \\(ssid=(\\S+),");
        int pos = 0;
        if ((pos = rx.indexIn(metaInfo)) == -1)
        {
            result = false;
            return wifiMacInfo;
        }
        wifiMacInfo.SSid = rx.cap(1).toAscii().data();
    }
    if(wifiMacInfo.type == "MGT_ASSOCIATION_RESPONSE")
    {
        QRegExp rx("ns3::MgtAssocResponseHeader \\(status code=(\\S+), rates");
        int pos = 0;
        if ((pos = rx.indexIn(metaInfo)) == -1)
        {
            result = false;
            return wifiMacInfo;
        }
        wifiMacInfo.assocResponseStatus = rx.cap(1).toAscii().data();
    }
    result = true;
    return wifiMacInfo;
}

AodvInfo
AnimPacket::parseAodv(QString metaInfo, bool & result)
{
    AodvInfo aodvInfo;

    QRegExp rx("ns3::aodv::TypeHeader \\((\\S+)\\) ");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return aodvInfo;
    }
    aodvInfo.type = rx.cap(1).toAscii().data();
    if(aodvInfo.type == "RREQ")
    {
        QRegExp rx("ns3::aodv::RreqHeader \\(RREQ ID \\d+ destination: ipv4 (\\S+) sequence number (\\d+) source: ipv4 (\\S+) sequence number \\d+");
        int pos = 0;
        if ((pos = rx.indexIn(metaInfo)) == -1)
        {
            result = false;
            return aodvInfo;
        }
        aodvInfo.destination = rx.cap(1).toAscii().data();
        aodvInfo.seq = rx.cap(2).toAscii().data();
        aodvInfo.source = rx.cap(1).toAscii().data();

    }
    if(aodvInfo.type == "RREP")
    {
        QRegExp rx("ns3::aodv::RrepHeader \\(destination: ipv4 (\\S+) sequence number (\\d+) source ipv4 (\\S+) ");
        int pos = 0;
        if ((pos = rx.indexIn(metaInfo)) == -1)
        {
            result = false;
            return aodvInfo;
        }
        aodvInfo.destination = rx.cap(1).toAscii().data();
        aodvInfo.seq = rx.cap(2).toAscii().data();
        aodvInfo.source = rx.cap(1).toAscii().data();
    }
    if(aodvInfo.type == "RERR")
    {
        QRegExp rx("ns3::aodv::RerrHeader \\(([^\\)]+) \\(ipv4 address, seq. number):(\\S+) ");
        int pos = 0;
        if ((pos = rx.indexIn(metaInfo)) == -1)
        {
            result = false;
            return aodvInfo;
        }
        aodvInfo.rerrInfo = rx.cap(1).toAscii().data();
        aodvInfo.destination = rx.cap(2).toAscii().data();
    }
    result = true;
    return aodvInfo;

}

DsdvInfo
AnimPacket::parseDsdv(QString metaInfo, bool & result)
{
    DsdvInfo dsdvInfo;

    QRegExp rx("ns3::dsdv::DsdvHeader");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return dsdvInfo;
    }
    result = true;
    return dsdvInfo;

}

OlsrInfo
AnimPacket::parseOlsr(QString metaInfo, bool & result)
{
    OlsrInfo olsrInfo;

    QRegExp rx("ns3::olsr::MessageHeader");
    int pos = 0;
    if ((pos = rx.indexIn(metaInfo)) == -1)
    {
        result = false;
        return olsrInfo;
    }
    result = true;
    return olsrInfo;
}







#if 0
void
AnimPacket::update (qreal t)
{
  qreal timeElapsed = t - getFirstBitTx ();
  qreal distanceTravelled = m_velocity * timeElapsed;
  m_distanceTraveled = distanceTravelled;
  qreal x = m_distanceTraveled * m_cos;
  qreal y = m_distanceTraveled * m_sin;
  m_head = QPointF (m_fromPos.x () + x,  m_fromPos.y () + y);
  //NS_LOG_DEBUG ("Upd Time:" << t << " Head:" << m_head << " Distance traveled:" << m_distanceTraveled << " time elapsed:" << timeElapsed  << " velocity:" << m_velocity);
}

#else
void
AnimPacket::update (qreal t)
{
    Q_UNUSED(t);
  qreal midPointX = (m_toPos.x() + m_fromPos.x())/2;
  qreal midPointY = (m_toPos.y() + m_fromPos.y())/2;
  m_head = QPointF (midPointX, midPointY);
  //m_head = QPointF (100,100);
  //NS_LOG_DEBUG ("m_head:" << m_head);
}

#endif
QRectF
AnimPacket::boundingRect () const
{
  return m_boundingRect;
  //QRectF r = QRectF(-m_boundingRect.width(),  -m_boundingRect.height(), m_boundingRect.width(), m_boundingRect.height());
  //return r;
}


void
AnimPacket::paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    //NS_LOG_DEBUG ("Packet Transform:" << transform());
    //NS_LOG_DEBUG ("Device Transform:" << painter->deviceTransform());
    //NS_LOG_DEBUG ("Scene Transform:" << sceneTransform());
    QPen p;
    QTransform viewTransform = AnimatorView::getInstance()->getTransform();

    painter->save();
    QPainterPath arrowTailPath;
    arrowTailPath.moveTo(0, 0);
    arrowTailPath.lineTo (-5 * (10/viewTransform.m22()) , 0);
    p.setColor(Qt::red);
    painter->setPen(p);
    //p.setWidthF(1.0);
    painter->setPen(p);
    painter->rotate (360 - m_line.angle ());
    painter->drawPath(arrowTailPath);
    painter->restore();


    QPolygonF arrowHeadPolygon;

  QPainterPath arrowHeadPath;
  qreal arrowHeadLength = 2 * (10/viewTransform.m22());
  arrowHeadPolygon << QPointF (0, 0) << QPointF (-arrowHeadLength * cos (PI/10), -arrowHeadLength * sin (PI/10)) << QPointF (-arrowHeadLength * cos (PI/10), arrowHeadLength * sin (PI/10));

  arrowHeadPath.lineTo (-arrowHeadLength * cos (PI/10), -arrowHeadLength * sin (PI/10));
  arrowHeadPath.moveTo (0, 0);
  arrowHeadPath.lineTo (-arrowHeadLength * cos (PI/10), arrowHeadLength * sin (PI/10));
  arrowHeadPath.moveTo (0, 0);

  arrowHeadPath.moveTo (0, 0);
  painter->save();
  QPen arrowHeadPen;
  QColor black (0, 0, 5, 130);
  arrowHeadPen.setColor(black);
  //p.setWidthF(1.1);


  painter->setPen(arrowHeadPen);
  painter->rotate (360 - m_line.angle ());
  QBrush brush;
  brush.setColor(black);
  brush.setStyle(Qt::SolidPattern);
  painter->setBrush(brush);
  painter->drawPolygon(arrowHeadPolygon);
  //painter->drawPath(arrowHeadPath);
  painter->restore();




  QPainterPath path;
  path.moveTo(0, 0);
  path.addPath(arrowHeadPath);
  path.moveTo(0, 0);
  path.addPath(arrowTailPath);


  m_boundingRect = path.boundingRect ();
  QTransform t;
  t.rotate(360 - m_line.angle ());
  m_boundingRect = t.mapRect(m_boundingRect);





  painter->save();
  QTransform textTransform;
  qreal textAngle = m_line.angle ();
  if(textAngle < 90)
  {
      textAngle = 360-textAngle;
  }
  else if (textAngle > 270)
  {
      textAngle = 360-textAngle;
  }
  else
  {
    textAngle = 180-textAngle;
  }
  painter->rotate(textAngle);
  textTransform.rotate(textAngle);
  QPainterPath textPath;
  QFont f ;//("Helvetica");//= painter->font();
  f.setKerning(false);
  f.setStyleHint(QFont::Times);
  //f.setPointSizeF(8/viewTransform.m22());
  //f.setPixelSize(5);
  f.setPointSizeF(15/viewTransform.m22());
  f.setFixedPitch(true);

  QPen p1 = painter->pen();
  p1.setColor(Qt::red);
  p1.setStyle(Qt::SolidLine);
  QBrush brush2 = painter->brush();
  brush2.setStyle(Qt::SolidPattern);
  brush2.setColor(Qt::black);
  p1.setWidthF(1/viewTransform.m22());
  p1.setBrush(brush2);
  //p1.setCosmetic(true);
  painter->setBrush(brush2);
  painter->setPen(p1);
  textPath.addText(0, -2/viewTransform.m22(), f, "Jo");


  painter->setTransform(m_infoText->transform());
  //QLineF l (m_fromPos, m_toPos);
  //painter->drawEllipse(m_fromPos, l.length(), l.length());
  //painter->drawText(0, 0, "Jo");


  QRectF textBoundingRect = textTransform.mapRect(textPath.boundingRect());

  painter->restore ();
  m_boundingRect = QRectF(QPointF(qMin (m_boundingRect.left(), textBoundingRect.left()),
                          qMin (m_boundingRect.top(), textBoundingRect.top())),
                          QPointF(qMax (m_boundingRect.right(), textBoundingRect.right()),
                          qMax (m_boundingRect.bottom(), textBoundingRect.bottom())));


  //NS_LOG_DEBUG ("m_boundingRect:" << m_boundingRect);


}


QPointF
AnimPacket::getHead ()
{
  return m_head;
}

QPointF
AnimPacket::getFromPos()
{
    return m_fromPos;
}

QPointF
AnimPacket::getToPos()
{
    return m_toPos;
}

AnimPacketMgr::AnimPacketMgr()
{
}
AnimPacketMgr *
AnimPacketMgr::getInstance()
{
    if(!pAnimPacketMgr)
    {
        pAnimPacketMgr = new AnimPacketMgr;
    }
    return pAnimPacketMgr;
}

AnimPacket *
AnimPacketMgr::add(uint32_t fromId, uint32_t toId, qreal fbTx, qreal fbRx, bool isWPacket, QString metaInfo, bool showMetaInfo)
{

    /*if (fromId != 0)
        return;
    if (toId != 3)
        return;
    if (m_packets.getCount())
        return;*/
    AnimPacket * pkt = new AnimPacket(fromId, toId, fbTx, fbRx, isWPacket, metaInfo, showMetaInfo);
    //NS_LOG_DEBUG ("FbTx:" << fbTx);
    //m_packets.add(fbTx, pkt);
    return pkt;
}



}


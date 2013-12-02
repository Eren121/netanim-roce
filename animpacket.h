#ifndef ANIMPACKET_H
#define ANIMPACKET_H
#include "qglobal.h"
#include <QGraphicsItem>
#include "animatorconstants.h"
#include "common.h"
#include "timevalue.h"
#include "animevent.h"
namespace netanim {


class AnimWirelessCircles : public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)

};


struct ArpInfo
{
    ArpInfo()
    {
        type = "null";
        sourceMac = "null";
        sourceIpv4 = "null";
        destMac = "ff:ff:ff:ff:ff:ff";
        destIpv4 = "null";
    }
    std::string toString()
    {
        return  " Arp "     + type       +
                " SMac: "   + sourceMac  +
                " DMac: "   + destMac    +
                " SrcIp : " + sourceIpv4 +
                " DstIp : " + destIpv4;
    }
    std::string type;
    std::string sourceMac;
    std::string sourceIpv4;
    std::string destMac;
    std::string destIpv4;
};

struct PppInfo
{
    std::string toString()
    {
        return " PPP";
    }

};

struct EthernetInfo
{
    EthernetInfo()
    {
        sourceMac = "null";
        destMac = "null";
    }
    std::string toString()
    {
        return  " Ethernet SMac: " + sourceMac +
                " DMac: "          + destMac;
    }
    std::string sourceMac;
    std::string destMac;
};


struct WifiMacInfo
{
    WifiMacInfo()
    {
        type = "null";
        toDs = "null";
        fromDs = "null";
        Da = "null";
        Sa = "null";
        Bssid = "null";
        Ra = "null";
        SSid = "null";
        assocResponseStatus = "null";

    }

    std::string toString()
    {
        if(type == "CTL_ACK")
            return " Wifi CTL_ACK RA:" + Ra;
        if(type == "CTL_RTS")
            return " Wifi CTL_RTS RA:" + Ra + " TA:" + Sa;
        if(type == "CTL_CTS")
            return " Wifi CTL_CTS RA:" + Ra;
        std::string temp = " Wifi " + type +
                " FromDS: " + fromDs +
                " toDS: " + toDs +
                " DA: " + Da +
                " SA: " + Sa +
                " BSSId: " + Bssid;
        if(type == "MGT_ASSOCIATION_REQUEST")
            temp += " SSid: " + SSid;

        if(type == "MGT_ASSOCIATION_RESPONSE")
            temp += " status: " + assocResponseStatus;
        return temp;
    }
    std::string type;
    std::string toDs;
    std::string fromDs;
    std::string Da;
    std::string Sa;
    std::string Bssid;
    std::string Ra;
    std::string SSid;
    std::string assocResponseStatus;
};


struct Ipv4Info
{
    Ipv4Info()
    {

    }
    std::string toString ()
    {
        return  " Ipv4 Proto:" + protocol +
                " SrcIp: " + SrcIp +
                " DstIp: " + DstIp;
    }
    std::string tos;
    std::string Dscp;
    std::string Ecn;
    std::string Ttl;
    std::string Id;
    std::string protocol;
    std::string length;
    std::string SrcIp;
    std::string DstIp;

};


struct IcmpInfo
{
    IcmpInfo()
    {

    }
    std::string toString()
    {
        std::string temp;
        temp += "ICMP type: " + type +
                "code: " + code;
        if (type == "3" && code == "3")
            temp += " DstUnreachable";
        return temp;

    }
    std::string type;
    std::string code;
};


struct UdpInfo
{
    UdpInfo()
    {

    }
    std::string toString()
    {
        return " UDP " + SPort + " > " + DPort;

    }
    std::string length;
    std::string SPort;
    std::string DPort;

};

struct TcpInfo
{
    TcpInfo()
    {

    }
    std::string toString()
    {
        return " TCP " + SPort + " > " + DPort +
                " " + flags +  " Seq=" + seq   +
                " Ack=" + ack + " Win=" + window;

    }
    std::string SPort;
    std::string DPort;
    std::string flags;
    std::string seq;
    std::string ack;
    std::string window;

};

struct AodvInfo
{
    AodvInfo()
    {

    }
    std::string toString()
    {
        if(type == "RERR")
        {
            return "RERR:" + rerrInfo + " " + destination;
        }
        return "AODV:" + type + " D=" + destination + " S=" + source + " Seq=" + seq;
    }
    std::string toShortString()
    {
        if(type == "RERR")
        {
            return "RERR:" + rerrInfo + " " + destination;
        }
        return "AODV:" + type + " D=" + destination + " S=" + source + " Seq=" + seq;
    }
    std::string type;
    std::string destination;
    std::string source;
    std::string seq;
    std::string rerrInfo;
};

struct DsdvInfo
{
    DsdvInfo()
    {

    }
    std::string toString()
    {
        return "DSDV";
    }
    std::string toShortString()
    {
        return "DSDV";
    }
};

struct OlsrInfo
{
    OlsrInfo()
    {

    }
    std::string toString()
    {
        return "OLSR";
    }
    std::string toShortString()
    {
        return "OLSR";
    }
};



class AnimPacket : public QObject, public QGraphicsItem, public AnimEvent
{
Q_OBJECT

    Q_PROPERTY (QPointF pos READ pos WRITE setPos)
public:
  AnimPacket(uint32_t fromNodeId,
             uint32_t toNodeId,
             qreal firstBitTx,
             qreal firstBitRx,
             bool isWPacket,
             QString metaInfo);
  ~AnimPacket();
  enum { Type = ANIMPACKET_TYPE };
  int type () const
  {
      return Type;
  }
  qreal getFirstBitTx ();
  qreal getFirstBitRx ();
  uint32_t getFromNodeId ();
  uint32_t getToNodeId ();
  QPointF getFromPos ();
  QPointF getToPos ();
  void update (qreal t);
  virtual QRectF boundingRect () const;
  void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
  QPointF getHead ();
  QGraphicsSimpleTextItem * getInfoTextItem();
  bool getIsWPacket ();
  QString getShortMeta (QString metaInfo);

private:
  uint32_t m_fromNodeId;
  uint32_t m_toNodeId;
  qreal m_firstBitTx;
  qreal m_firstBitRx;
  qreal m_velocity;
  qreal m_isWPacket;
  qreal m_distanceTraveled;
  QLineF m_line;
  qreal m_cos;
  qreal m_sin;
  QPointF m_fromPos;
  QPointF m_toPos;
  QPointF m_head;
  QRectF m_boundingRect;
  QGraphicsSimpleTextItem * m_infoText;


  ArpInfo parseArp(std::string metaInfo, bool & result);
  PppInfo parsePpp(std::string metaInfo, bool & result);
  EthernetInfo parseEthernet(std::string metaInfo, bool & result);
  WifiMacInfo parseWifi(std::string metaInfo, bool & result);
  Ipv4Info parseIpv4(std::string metaInfo, bool & result);
  IcmpInfo parseIcmp(std::string metaInfo, bool & result);
  UdpInfo parseUdp(std::string metaInfo, bool & result);
  TcpInfo parseTcp(std::string metaInfo, bool & result);
  AodvInfo parseAodv(std::string metaInfo, bool & result);
  DsdvInfo parseDsdv(std::string metaInfo, bool & result);
  OlsrInfo parseOlsr(std::string metaInfo, bool & result);

};

class AnimPacketMgr
{
public:
    static AnimPacketMgr * getInstance();
    AnimPacket * add(uint32_t fromId, uint32_t toId, qreal fbTx, qreal fbRx, bool isWPacket, QString metaInfo);
private:
    AnimPacketMgr();


};

}
#endif // ANIMPACKET_H

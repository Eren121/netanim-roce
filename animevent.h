#ifndef ANIMEVENT_H
#define ANIMEVENT_H

#include <stdint.h>
#include <Qt>
namespace netanim {

class AnimEvent
{

public:
    typedef enum {
        PACKET_EVENT,
        ADD_NODE_EVENT,
        UPDATE_NODE_EVENT
    } AnimEventType_h;
    AnimEventType_h m_type;
    AnimEvent(AnimEventType_h type): m_type (type)
    {
    }
};


class AnimNodeAddEvent: public AnimEvent
{
public:
    AnimNodeAddEvent(uint32_t nodeId, qreal x, qreal y, QString nodeDescription):
        AnimEvent(ADD_NODE_EVENT),
        m_nodeId(nodeId),
        m_x(x),
        m_y(y),
        m_nodeDescription(nodeDescription)
    {
    }
    uint32_t m_nodeId;
    qreal m_x;
    qreal m_y;
    QString m_nodeDescription;


};


class AnimPacketEvent: public AnimEvent
{
public:
    AnimPacketEvent(uint32_t fromId, uint32_t toId, qreal fbTx, qreal fbRx, bool isWPacket):
        AnimEvent(PACKET_EVENT),
        m_fromId(fromId),
        m_toId(toId),
        m_fbTx(fbTx),
        m_fbRx(fbRx),
        m_isWPacket(isWPacket)
    {
    }
    uint32_t m_fromId;
    uint32_t m_toId;
    qreal m_fbTx;
    qreal m_fbRx;
    bool m_isWPacket;


};




} // namespace netanim
#endif // ANIMEVENT_H

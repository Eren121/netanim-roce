#include "animpacket.h"

AnimPacket::AnimPacket(uint32_t fromNodeId, uint32_t toNodeId, qreal firstBitTx, qreal lastBitTx, qreal firstBitRx, qreal lastBitRx):
    m_fromNodeId(fromNodeId),
    m_toNodeId(toNodeId),
    m_firstBitTx(firstBitTx),
    m_lastBitTx(lastBitTx),
    m_firstBitRx(firstBitRx),
    m_lastBitRx(lastBitRx)
{


}

uint32_t AnimPacket::getFromNodeId()
{
    return m_fromNodeId;
}

uint32_t AnimPacket::getToNodeId()
{
    return m_toNodeId;
}

qreal AnimPacket::getFirstBitTx()
{
    return m_firstBitTx;
}

qreal AnimPacket::getFirstBitRx()
{
    return m_firstBitRx;
}

qreal AnimPacket::getLastBitRx()
{
    return m_lastBitRx;
}

qreal AnimPacket::getLastBitTx()
{
    return m_lastBitTx;
}

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


qreal AnimPacket::getFirstBitTx()
{
    return m_firstBitTx;
}

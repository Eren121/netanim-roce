#ifndef ANIMPACKET_H
#define ANIMPACKET_H
#include "common.h"
#include "qglobal.h"

class AnimPacket {
public:
    AnimPacket(uint32_t fromNodeId,
               uint32_t toNodeId,
               qreal firstBitTx,
               qreal lastBitTx,
               qreal firstBitRx,
               qreal lastBitRx);
    qreal getFirstBitTx();
    qreal getFirstBitRx();
    qreal getLastBitTx();
    qreal getLastBitRx();
    uint32_t getFromNodeId();
    uint32_t getToNodeId();

private:
    uint32_t m_fromNodeId;
    uint32_t m_toNodeId;
    qreal m_firstBitTx;
    qreal m_lastBitTx;
    qreal m_firstBitRx;
    qreal m_lastBitRx;
};

#endif // ANIMPACKET_H

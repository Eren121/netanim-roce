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
    AnimNodeAddEvent(uint32_t nodeId, qreal x, qreal y):
        AnimEvent(ADD_NODE_EVENT),
        m_nodeId(nodeId),
        m_x(x),
        m_y(y)
    {
    }
    uint32_t m_nodeId;
    qreal m_x;
    qreal m_y;


};




} // namespace netanim
#endif // ANIMEVENT_H

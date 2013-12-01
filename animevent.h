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
        UPDATE_NODE_POS_EVENT,
        UPDATE_NODE_COLOR_EVENT,
        UPDATE_NODE_DESCRIPTION_EVENT,
        UPDATE_NODE_SIZE_EVENT,
        UPDATE_NODE_IMAGE_EVENT,
        ADD_LINK_EVENT,
        UPDATE_LINK_EVENT
    } AnimEventType_h;
    AnimEventType_h m_type;
    AnimEvent(AnimEventType_h type): m_type (type)
    {
    }
};


class AnimNodeAddEvent: public AnimEvent
{
public:
    AnimNodeAddEvent(uint32_t nodeId, qreal x, qreal y, QString nodeDescription, uint8_t r, uint8_t g, uint8_t b):
        AnimEvent(ADD_NODE_EVENT),
        m_nodeId(nodeId),
        m_x(x),
        m_y(y),
        m_nodeDescription(nodeDescription),
        m_r(r),
        m_g(g),
        m_b(b)
    {
    }
    uint32_t m_nodeId;
    qreal m_x;
    qreal m_y;
    QString m_nodeDescription;
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;


};


class AnimLinkAddEvent: public AnimEvent
{

public:
    AnimLinkAddEvent(uint32_t fromNodeId, uint32_t toNodeId, QString linkDescription, QString fromNodeDescription, QString toNodeDescription):
        AnimEvent(ADD_LINK_EVENT),
        m_fromNodeId(fromNodeId),
        m_toNodeId(toNodeId),
        m_linkDescription(linkDescription),
        m_fromNodeDescription(fromNodeDescription),
        m_toNodeDescription(toNodeDescription)
    {
    }
    uint32_t m_fromNodeId;
    uint32_t m_toNodeId;
    QString m_linkDescription;
    QString m_fromNodeDescription;
    QString m_toNodeDescription;
};

class AnimLinkUpdateEvent: public AnimEvent
{

public:
    AnimLinkUpdateEvent(uint32_t fromNodeId, uint32_t toNodeId, QString linkDescription):
        AnimEvent(UPDATE_LINK_EVENT),
        m_fromNodeId(fromNodeId),
        m_toNodeId(toNodeId),
        m_linkDescription(linkDescription)
    {
    }
    uint32_t m_fromNodeId;
    uint32_t m_toNodeId;
    QString m_linkDescription;
};





class AnimNodePositionUpdateEvent: public AnimEvent
{
public:
    AnimNodePositionUpdateEvent(uint32_t nodeId, qreal x, qreal y):
        AnimEvent(UPDATE_NODE_POS_EVENT),
        m_nodeId(nodeId),
        m_x(x),
        m_y(y)
    {
    }
    uint32_t m_nodeId;
    qreal m_x;
    qreal m_y;
};


class AnimNodeColorUpdateEvent: public AnimEvent
{
public:
    AnimNodeColorUpdateEvent(uint32_t nodeId, uint8_t r, uint8_t g, uint8_t b):
        AnimEvent(UPDATE_NODE_COLOR_EVENT),
        m_nodeId(nodeId),
        m_r(r),
        m_g(g),
        m_b(b)
    {
    }
    uint32_t m_nodeId;
    uint8_t m_r;
    uint8_t m_g;
    uint8_t m_b;

};


class AnimNodeSizeUpdateEvent: public AnimEvent
{
public:
    AnimNodeSizeUpdateEvent(uint32_t nodeId, double width, double height):
        AnimEvent(UPDATE_NODE_SIZE_EVENT),
        m_nodeId(nodeId),
        m_width(width),
        m_height(height)
    {
    }
    uint32_t m_nodeId;
    uint8_t m_width;
    uint8_t m_height;

};

class AnimNodeDescriptionUpdateEvent: public AnimEvent
{
public:
    AnimNodeDescriptionUpdateEvent(uint32_t nodeId, QString description):
        AnimEvent(UPDATE_NODE_DESCRIPTION_EVENT),
        m_nodeId(nodeId),
        m_description(description)
    {
    }
    uint32_t m_nodeId;
    QString m_description;

};



class AnimNodeImageUpdateEvent: public AnimEvent
{
public:
    AnimNodeImageUpdateEvent(uint32_t nodeId, uint32_t resourceId):
        AnimEvent(UPDATE_NODE_IMAGE_EVENT),
        m_nodeId(nodeId),
        m_resourceId(resourceId)
    {
    }
    uint32_t m_nodeId;
    uint32_t m_resourceId;

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

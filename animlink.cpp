#include <animlink.h>
#include <animnode.h>
#include "animatorconstants.h"

namespace netanim {

AnimLinkMgr * pAnimLinkMgr = 0;

AnimLink::AnimLink (uint32_t fromId, uint32_t toId):
    m_fromId(fromId),
    m_toId(toId)
{

    AnimNodeMgr *pAnimNodeMgr = AnimNodeMgr::getInstance();
    AnimNode * fromNode = pAnimNodeMgr->getNode(fromId);
    QPointF fromNodeCenter = fromNode->getCenter();


    AnimNode * toNode = pAnimNodeMgr->getNode(toId);
    QPointF toNodeCenter = toNode->getCenter();
    QLineF l (fromNodeCenter, toNodeCenter);
    setLine(l);
    setZValue(ANIMLINK_ZVALUE);
}


AnimLinkMgr::AnimLinkMgr()
{

}

AnimLinkMgr *
AnimLinkMgr::getInstance()
{
    if (!pAnimLinkMgr)
    {
        pAnimLinkMgr = new AnimLinkMgr;
    }
    return pAnimLinkMgr;
}


void
AnimLinkMgr::add(uint32_t fromId, uint32_t toId)
{
    AnimLink * link = new AnimLink(fromId, toId);
    if (m_links.find (fromId) == m_links.end())
    {
        AnimLinkVector_t  tmp;
        m_links[fromId] = tmp;
    }
    AnimLinkVector_t & v = m_links[fromId];
    v.push_back(link);

}

AnimLinkMgr::NodeIdAnimLinkVectorMap_t *
AnimLinkMgr::getLinks()
{
    return &m_links;
}

} // namespace netanim

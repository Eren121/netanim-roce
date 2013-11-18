#ifndef ANIMLINK_H
#define ANIMLINK_H

#include <stdint.h>
#include <map>
#include <QGraphicsLineItem>

namespace netanim {

class AnimLink : public QGraphicsLineItem
{
public:
    AnimLink(uint32_t fromId, uint32_t toId);
private:
    uint32_t m_fromId;
    uint32_t m_toId;
};


class AnimLinkMgr
{
public:
    static AnimLinkMgr * getInstance ();
    void add (uint32_t fromId, uint32_t toId);
    typedef std::vector <AnimLink *> AnimLinkVector_t;
    typedef std::map <uint32_t, AnimLinkVector_t> NodeIdAnimLinkVectorMap_t;

    NodeIdAnimLinkVectorMap_t * getLinks ();

private:
    AnimLinkMgr();
    NodeIdAnimLinkVectorMap_t m_links;

};


} // namespace netanim
#endif // ANIMLINK_H

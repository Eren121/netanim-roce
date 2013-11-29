#ifndef ANIMRESOURCE_H
#define ANIMRESOURCE_H

#include <Qt>
#include <map>
#include <stdint.h>


class AnimResourceManager
{
public:
    static AnimResourceManager * getInstance();
    void add(uint32_t resourceId, QString resourcePath);
    QString get(uint32_t resourceid);
private:
    AnimResourceManager();
    std::map <uint32_t, QString> m_resources;

};
#endif // ANIMRESOURCE_H

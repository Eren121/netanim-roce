#include "animresource.h"
#include "fatal-error.h"
#include <QString>

AnimResourceManager * pResourceManager = 0;

AnimResourceManager::AnimResourceManager()
{

}

AnimResourceManager *
AnimResourceManager::getInstance()
{
    if(!pResourceManager)
    {
        pResourceManager = new AnimResourceManager;
    }
    return pResourceManager;
}


void
AnimResourceManager::add(uint32_t resourceId, QString resourcePath)
{
    m_resources[resourceId] = resourcePath;
}


QString
AnimResourceManager::get(uint32_t resourceid)
{
    if(m_resources.find(resourceid) == m_resources.end())
    {
        NS_FATAL_ERROR ("Unable to find resource:" << resourceid);
    }
    return m_resources[resourceid];
}

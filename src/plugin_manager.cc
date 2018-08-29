#include "plugin_manager.h"
#include "plugin.h"

namespace cpp_plugin
{

void PluginManager::RegisterPlugin(Plugin* plugin)
{
    m_mutex.lock();
    m_plugins[plugin->channel()]=plugin;
    m_mutex.unlock();
}


void PluginManager::UnRegisterPlugin(Plugin* plugin)
{
    m_mutex.lock();
    auto find = m_plugins.find(plugin->channel());
    if(find!=m_plugins.end())
        m_plugins.erase(find);
    m_mutex.unlock();
}

void PluginManager::HandleMethodCall(const std::string &channel,const uint8_t* data,size_t len,
                        std::unique_ptr<MethodResult> result)
{
    m_mutex.lock();
    auto find = m_plugins.find(channel);
    if(find!=m_plugins.end())
    {
        Plugin* plugin = find->second;
        std::unique_ptr<MethodCall> method_call = plugin->GetCodec().DecodeMethodCallInternal(data,len);
        find->second->HandleMethodCall(*method_call,std::move(result));
    }
    m_mutex.unlock();   
}

Plugin* PluginManager::GetPlugin(const std::string &channel)
{
    m_mutex.lock();
    auto find = m_plugins.find(channel);
    m_mutex.unlock();

    if(find!=m_plugins.end())
        return find->second;
    else
        return NULL;
}

}//namespace







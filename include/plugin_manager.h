#ifndef CPP_PLUGIN_PLUGIN_MANAGER_H_
#define CPP_PLUGIN_PLUGIN_MANAGER_H_

#include <map>
#include <mutex>
#include <string>
#include "method_call.h"
#include "method_codec.h"
#include "method_result.h"

namespace cpp_plugin {

class Plugin;

//管理插件
class PluginManager
{
public:
    static PluginManager* Instance();

    virtual void RegisterPlugin(Plugin* plugin);
    virtual void UnRegisterPlugin(Plugin* plugin);

    //调用dart
    virtual void InvokeMethodCall(const std::string &channel,const uint8_t* data,size_t len) =0;

    //调用C++函数处理
    void HandleMethodCall(const std::string &channel,const uint8_t* data,size_t len,
                                  std::unique_ptr<MethodResult> result);

    Plugin* GetPlugin(const std::string &channel);
private:
  std::map<std::string,Plugin*> m_plugins;
  std::mutex m_mutex;
};

}//namespace
#endif

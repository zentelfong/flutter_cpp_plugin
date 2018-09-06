#ifndef CPP_PLUGIN_PLUGIN_MANAGER_H_
#define CPP_PLUGIN_PLUGIN_MANAGER_H_

#include <map>
#include <mutex>
#include <string>
#include "plugin.h"

namespace cpp_plugin {

//管理插件
class PluginManager
{
public:
    static PluginManager* Instance();

    PluginManager(PluginManager const &) = delete;
    PluginManager &operator=(PluginManager const &) = delete;

    //注册插件
    virtual void RegisterPlugin(Plugin* plugin);
    virtual void UnRegisterPlugin(Plugin* plugin);

    //调用dart
    virtual void InvokeMethodCall(const std::string &channel,const uint8_t* data,size_t len) =0;

    //调用C++函数处理
    void HandleMethodCall(const std::string &channel,const uint8_t* data,size_t len,
                                  std::unique_ptr<MethodResult> result);

    Plugin* GetPlugin(const std::string &channel);
    
protected:
  PluginManager(){

  }
private:
  std::map<std::string,Plugin*> m_plugins;
  std::mutex m_mutex;
};

}//namespace

//插件的main函数
void plugin_main();

#endif

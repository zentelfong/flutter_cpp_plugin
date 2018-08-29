#include "plugin.h"
#include "json_method_codec.h"
#include "plugin_manager.h"

namespace cpp_plugin {


Plugin::Plugin(const std::string &channel)
    : channel_(channel){
}

Plugin::~Plugin() {
}


void Plugin::InvokeMethodCall(const MethodCall &method_call) {

  std::unique_ptr<std::vector<uint8_t>> message =
      GetCodec().EncodeMethodCall(method_call);

  PluginManager::Instance()->InvokeMethodCall(channel_,message->data(),message->size());
}


}  // namespace cpp_plugin

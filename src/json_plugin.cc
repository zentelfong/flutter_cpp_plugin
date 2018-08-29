#include "json_plugin.h"
#include "json_method_codec.h"

namespace cpp_plugin {

JsonPlugin::JsonPlugin(const std::string &channel)
    : Plugin(channel) {}

JsonPlugin::~JsonPlugin() {}

const MethodCodec &JsonPlugin::GetCodec() const {
  return JsonMethodCodec::GetInstance();
}

void JsonPlugin::HandleMethodCall(const MethodCall &method_call,
                                  std::unique_ptr<MethodResult> result) {
  HandleJsonMethodCall(dynamic_cast<const JsonMethodCall &>(method_call),
                       std::move(result));
}

void JsonPlugin::InvokeMethod(const std::string &method,
                              const Json::Value &arguments) {
  InvokeMethodCall(JsonMethodCall(method, arguments));
}

}  // namespace cpp_plugin

#include "standard_plugin.h"
#include "standard_method_codec.h"

namespace cpp_plugin {

StandardPlugin::StandardPlugin(const std::string &channel)
    : Plugin(channel) {}

StandardPlugin::~StandardPlugin() {}

const MethodCodec &StandardPlugin::GetCodec() const {
  return StandardMethodCodec::GetInstance();
}

void StandardPlugin::HandleMethodCall(const MethodCall &method_call,
                                  std::unique_ptr<MethodResult> result) {
  HandleStandardMethodCall(dynamic_cast<const StandardMethodCall &>(method_call),
                       std::move(result));
}

void StandardPlugin::InvokeMethod(const std::string &method,
						std::unique_ptr<StandardValue> arguments) {
  InvokeMethodCall(StandardMethodCall(method, std::move(arguments)));
}

}  // namespace cpp_plugin

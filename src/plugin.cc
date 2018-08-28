#include "plugin.h"
#include "json_method_codec.h"

namespace cpp_plugin {

Plugin::Plugin(const std::string &channel, bool input_blocking)
    : channel_(channel), input_blocking_(input_blocking) {}

Plugin::~Plugin() {}

void Plugin::InvokeMethodCall(const MethodCall &method_call) {

  std::unique_ptr<std::vector<uint8_t>> message =
      GetCodec().EncodeMethodCall(method_call);

  //FlutterPlatformMessage platform_message_response = {
  //    .struct_size = sizeof(FlutterPlatformMessage),
  //    .channel = channel_.c_str(),
  //    .message = message->data(),
  //    .message_size = message->size(),
  //};
  //FlutterEngineSendPlatformMessage(engine_, &platform_message_response);
}

}  // namespace cpp_plugin

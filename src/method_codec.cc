#include "method_codec.h"

namespace cpp_plugin {

MethodCodec::~MethodCodec() {}

std::unique_ptr<MethodCall> MethodCodec::DecodeMethodCall(
    const uint8_t *message, const size_t message_size) const {
  return DecodeMethodCallInternal(message, message_size);
}

std::unique_ptr<std::vector<uint8_t>> MethodCodec::EncodeMethodCall(
    const MethodCall &method_call) const {
  return EncodeMethodCallInternal(method_call);
}

std::unique_ptr<std::vector<uint8_t>> MethodCodec::EncodeSuccessEnvelope(
    const void *result) const {
  return EncodeSuccessEnvelopeInternal(result);
}

std::unique_ptr<std::vector<uint8_t>> MethodCodec::EncodeErrorEnvelope(
    const std::string &error_code, const std::string &error_message,
    const void *error_details) const {
  return EncodeErrorEnvelopeInternal(error_code, error_message, error_details);
}

}  // namespace cpp_plugin

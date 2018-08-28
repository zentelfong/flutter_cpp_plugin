#ifndef CPP_PLUGIN_JSON_METHOD_CODEC_H_
#define CPP_PLUGIN_JSON_METHOD_CODEC_H_

#include <json/json.h>

#include "method_codec.h"

namespace cpp_plugin {

// An implementation of MethodCodec that uses JSON strings as the serialization.
//
// void* types in this implementation must always be Json::Value* types (from
// the jsoncpp library).
class JsonMethodCodec : public MethodCodec {
 public:
  // Returns the shared instance of the codec.
  static const JsonMethodCodec &GetInstance();

  ~JsonMethodCodec() = default;

  // Prevent copying.
  JsonMethodCodec(JsonMethodCodec const &) = delete;
  JsonMethodCodec &operator=(JsonMethodCodec const &) = delete;

 protected:
  // Instances should be obtained via GetInstance.
  JsonMethodCodec() = default;

  // MethodCodec:
  std::unique_ptr<MethodCall> DecodeMethodCallInternal(
      const uint8_t *message, const size_t message_size) const override;
  std::unique_ptr<std::vector<uint8_t>> EncodeMethodCallInternal(
      const MethodCall &method_call) const override;
  std::unique_ptr<std::vector<uint8_t>> EncodeSuccessEnvelopeInternal(
      const void *result) const override;
  std::unique_ptr<std::vector<uint8_t>> EncodeErrorEnvelopeInternal(
      const std::string &error_code, const std::string &error_message,
      const void *error_details) const override;

 private:
  // Serializes |json| into a byte stream.
  std::unique_ptr<std::vector<uint8_t>> EncodeJsonObject(
      const Json::Value &json) const;
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_JSON_METHOD_CODEC_H_

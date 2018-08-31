#ifndef CPP_PLUGIN_STANDARD_METHOD_CODEC_H_
#define CPP_PLUGIN_STANDARD_METHOD_CODEC_H_

#include <json/json.h>

#include "method_codec.h"

namespace cpp_plugin {

class StandardMethodCodec : public MethodCodec {
 public:
  // Returns the shared instance of the codec.
  static const StandardMethodCodec &GetInstance();

  ~StandardMethodCodec() = default;

  // Prevent copying.
  StandardMethodCodec(StandardMethodCodec const &) = delete;
  StandardMethodCodec &operator=(StandardMethodCodec const &) = delete;

 protected:
  // Instances should be obtained via GetInstance.
  StandardMethodCodec() = default;

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
  
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_STANDARD_METHOD_CODEC_H_

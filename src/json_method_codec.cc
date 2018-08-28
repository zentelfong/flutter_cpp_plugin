#include "json_method_codec.h"
#include <iostream>
#include "json_method_call.h"

namespace cpp_plugin {

namespace {
// Keys used in MethodCall encoding.
constexpr char kMessageMethodKey[] = "method";
constexpr char kMessageArgumentsKey[] = "args";
}  // namespace

// static
const JsonMethodCodec &JsonMethodCodec::GetInstance() {
  static JsonMethodCodec sInstance;
  return sInstance;
}

std::unique_ptr<MethodCall> JsonMethodCodec::DecodeMethodCallInternal(
    const uint8_t *message, const size_t message_size) const {
  Json::CharReaderBuilder reader_builder;
  std::unique_ptr<Json::CharReader> parser(reader_builder.newCharReader());

  auto raw_message = reinterpret_cast<const char *>(message);
  Json::Value json_message;
  std::string parse_errors;
  bool parsing_successful = parser->parse(
      raw_message, raw_message + message_size, &json_message, &parse_errors);
  if (!parsing_successful) {
    std::cerr << "Unable to parse JSON method call:" << std::endl
              << parse_errors << std::endl;
    return nullptr;
  }

  Json::Value method = json_message[kMessageMethodKey];
  if (method.isNull()) {
    return nullptr;
  }
  Json::Value arguments = json_message[kMessageArgumentsKey];
  return std::make_unique<JsonMethodCall>(method.asString(), arguments);
}

std::unique_ptr<std::vector<uint8_t>> JsonMethodCodec::EncodeMethodCallInternal(
    const MethodCall &method_call) const {
  Json::Value message(Json::objectValue);
  message[kMessageMethodKey] = method_call.method_name();
  message[kMessageArgumentsKey] =
      *static_cast<const Json::Value *>(method_call.arguments());

  return EncodeJsonObject(message);
}

std::unique_ptr<std::vector<uint8_t>>
JsonMethodCodec::EncodeSuccessEnvelopeInternal(const void *result) const {
  Json::Value envelope(Json::arrayValue);
  envelope.append(result == nullptr
                      ? Json::Value()
                      : *static_cast<const Json::Value *>(result));
  return EncodeJsonObject(envelope);
}

std::unique_ptr<std::vector<uint8_t>>
JsonMethodCodec::EncodeErrorEnvelopeInternal(const std::string &error_code,
                                             const std::string &error_message,
                                             const void *error_details) const {
  Json::Value envelope(Json::arrayValue);
  envelope.append(error_code);
  envelope.append(error_message.empty() ? Json::Value() : error_message);
  envelope.append(error_details == nullptr
                      ? Json::Value()
                      : *static_cast<const Json::Value *>(error_details));
  return EncodeJsonObject(envelope);
}

std::unique_ptr<std::vector<uint8_t>> JsonMethodCodec::EncodeJsonObject(
    const Json::Value &json) const {
  Json::StreamWriterBuilder writer_builder;
  std::string serialization = Json::writeString(writer_builder, json);

  return std::make_unique<std::vector<uint8_t>>(serialization.begin(),
                                                serialization.end());
}

}  // namespace cpp_plugin

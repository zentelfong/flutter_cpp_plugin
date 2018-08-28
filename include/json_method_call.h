#ifndef CPP_PLUGIN_JSON_METHOD_CALL_H_
#define CPP_PLUGIN_JSON_METHOD_CALL_H_

#include <string>

#include <json/json.h>

#include "method_call.h"

namespace cpp_plugin {

// A concrete implmentation of MethodCall for use with the JSON codec.
class JsonMethodCall : public MethodCall {
 public:
  // Creates a MethodCall with the given name and, optionally, arguments.
  explicit JsonMethodCall(const std::string &method_name,
                          const Json::Value &arguments = Json::Value());
  ~JsonMethodCall();

  // Prevent copying.
  JsonMethodCall(JsonMethodCall const &) = delete;
  JsonMethodCall &operator=(JsonMethodCall const &) = delete;

  // MethodCall:
  // Returns a pointer to a Json::Value object. This will never return null;
  // 'no arguments' is represented with a JSON::nullValue.
  const void *arguments() const override;

  // Returns a reference to the object pointed to by arguments().
  // This is a convience method for code that is interacting directly with a
  // JsonMethodCall to avoid casting and dereferencing.
  const Json::Value &GetArgumentsAsJson() const;

 private:
  Json::Value arguments_;
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_JSON_METHOD_CALL_H_

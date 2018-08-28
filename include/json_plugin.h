#ifndef CPP_PLUGIN_JSON_PLUGIN_H_
#define CPP_PLUGIN_JSON_PLUGIN_H_

#include "json_method_call.h"
#include "plugin.h"

namespace cpp_plugin {

// A base class for plugins using the JSON method codec.
//
// Provides a few utility shims from the type-agnostic Plugin class.
class JsonPlugin : public Plugin {
 public:
  // See Plugin for constructor details.
  explicit JsonPlugin(const std::string &channel, bool input_blocking = false);
  virtual ~JsonPlugin();

  // Prevent copying.
  JsonPlugin(JsonPlugin const &) = delete;
  JsonPlugin &operator=(JsonPlugin const &) = delete;

  // Plugin implementation:
  const MethodCodec &GetCodec() const override;
  void HandleMethodCall(const MethodCall &method_call,
                        std::unique_ptr<MethodResult> result) override;

 protected:
  // Identical to HandleMethodCall, except that the call has been cast to the
  // more specific type. Subclasses must implement this instead of
  // HandleMethodCall.
  virtual void HandleJsonMethodCall(const JsonMethodCall &method_call,
                                    std::unique_ptr<MethodResult> result) = 0;

  // Calls InvokeMethodCall with a JsonMethodCall constructed from the given
  // values.
  void InvokeMethod(const std::string &method,
                    const Json::Value &arguments = Json::Value());
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_JSON_PLUGIN_H_

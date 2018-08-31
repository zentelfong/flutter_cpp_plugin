#ifndef CPP_PLUGIN_STANDARD_PLUGIN_H_
#define CPP_PLUGIN_STANDARD_PLUGIN_H_

#include "standard_method_call.h"
#include "plugin.h"

namespace cpp_plugin {

class StandardPlugin : public Plugin {
 public:
  // See Plugin for constructor details.
  explicit StandardPlugin(const std::string &channel);
  virtual ~StandardPlugin();

  // Prevent copying.
  StandardPlugin(StandardPlugin const &) = delete;
  StandardPlugin &operator=(StandardPlugin const &) = delete;

  // Plugin implementation:
  const MethodCodec &GetCodec() const override;
  void HandleMethodCall(const MethodCall &method_call,
                   std::unique_ptr<MethodResult> result) override;

 protected:
  // Identical to HandleMethodCall, except that the call has been cast to the
  // more specific type. Subclasses must implement this instead of
  // HandleMethodCall.
  virtual void HandleStandardMethodCall(const StandardMethodCall &method_call,
                                    std::unique_ptr<MethodResult> result) = 0;

  // Calls InvokeMethodCall with a JsonMethodCall constructed from the given
  // values.
  void InvokeMethod(const std::string &method,std::unique_ptr<StandardValue> arguments);
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_STANDARD_PLUGIN_H_

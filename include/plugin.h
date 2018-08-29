#ifndef CPP_PLUGIN_PLUGIN_H_
#define CPP_PLUGIN_PLUGIN_H_

#include <functional>
#include <memory>
#include <string>

#include "method_call.h"
#include "method_codec.h"
#include "method_result.h"

namespace cpp_plugin {

// Represents a plugin that can be registered with the Flutter Embedder.
//
// A plugin listens on a platform channel and processes requests that come
// in on said channel.  See https://flutter.io/platform-channels/ for more
// details on what these channels look like.
class Plugin {
 public:
  // Constructs a plugin for a given channel.
  //
  // |input_blocking| Determines whether user input should be blocked during the
  // duration of this plugin's platform callback handler (in most cases this
  // can be set to false).
  explicit Plugin(const std::string &channel);
  virtual ~Plugin();

  // Returns the codec to use for this plugin.
  virtual const MethodCodec &GetCodec() const = 0;

  //处理dart调用
  virtual void HandleMethodCall(const MethodCall &method_call,
                                std::unique_ptr<MethodResult> result) = 0;

  // Returns the channel on which this plugin listens.
  virtual std::string channel() const { return channel_; }

 protected:
  //调用dart接口
  void InvokeMethodCall(const MethodCall &method_call);

 private:
  std::string channel_;
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_PLUGIN_H_

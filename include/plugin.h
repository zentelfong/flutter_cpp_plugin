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
  explicit Plugin(const std::string &channel, bool input_blocking = false);
  virtual ~Plugin();

  // Returns the codec to use for this plugin.
  virtual const MethodCodec &GetCodec() const = 0;

  // Handles a method call from Flutter on this platform's channel.
  //
  // Implementations must call exactly one of the methods on |result|,
  // exactly once. Failure to indicate a |result| is a memory leak.
  virtual void HandleMethodCall(const MethodCall &method_call,
                                std::unique_ptr<MethodResult> result) = 0;

  // Returns the channel on which this plugin listens.
  virtual std::string channel() const { return channel_; }

  // Determines whether this plugin blocks on input while it is running.
  //
  // If this is true, then the parent window should  disable input callbacks
  // while waiting for this plugin to handle its platform message.
  virtual bool input_blocking() const { return input_blocking_; }

 protected:
  // Calls a method in the Flutter engine on this Plugin's channel.
  void InvokeMethodCall(const MethodCall &method_call);

 private:
  std::string channel_;
  bool input_blocking_;
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_PLUGIN_H_

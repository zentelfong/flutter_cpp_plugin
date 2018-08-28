#ifndef CPP_PLUGIN_METHOD_CALL_H_
#define CPP_PLUGIN_METHOD_CALL_H_

#include <string>

namespace cpp_plugin {

// An object encapsulating a method call from Flutter.
class MethodCall {
 public:
  // Creates a MethodCall with the given name. Used only as a superclass
  // constructor for subclasses, which should also take the arguments.
  explicit MethodCall(const std::string &method_name);
  virtual ~MethodCall();

  // Prevent copying.
  MethodCall(MethodCall const &) = delete;
  MethodCall &operator=(MethodCall const &) = delete;

  // The name of the method being called.
  const std::string &method_name() const { return method_name_; }

  // The arguments to the method call, or NULL if there are none. The type of
  // the object being pointed to is determined by the concrete subclasses.
  virtual const void *arguments() const = 0;

 private:
  std::string method_name_;
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_METHOD_CALL_H_

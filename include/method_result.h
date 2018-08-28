#ifndef CPP_PLUGIN_METHOD_RESULT_H_
#define CPP_PLUGIN_METHOD_RESULT_H_

#include <string>

namespace cpp_plugin {

// Encapsulates a result sent back to the Flutter engine in response to a
// MethodCall. Only one method should be called on any given instance.
class MethodResult {
 public:
  MethodResult();
  virtual ~MethodResult();

  // Prevent copying.
  MethodResult(MethodResult const &) = delete;
  MethodResult &operator=(MethodResult const &) = delete;

  // Sends a success response, indicating that the call completed successfully.
  // An optional value can be provided as part of the success message. The value
  // must be a type handled by the channel's codec.
  void Success(const void *result = nullptr);

  // Sends an error response, indicating that the call was understood but
  // handling failed in some way. A string error code must be provided, and in
  // addition an optional user-readable error_message and/or details object can
  // be included. The details, if provided, must be a type handled by the
  // channel's codec.
  void Error(const std::string &error_code,
             const std::string &error_message = "",
             const void *error_details = nullptr);

  // Sends a not-implemented response, indicating that the method either was not
  // recognized, or has not been implemented.
  void NotImplemented();

 protected:
  // Internal implementation of the interface methods above, to be implemented
  // in subclasses.
  virtual void SuccessInternal(const void *result) = 0;
  virtual void ErrorInternal(const std::string &error_code,
                             const std::string &error_message,
                             const void *error_details) = 0;
  virtual void NotImplementedInternal() = 0;
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_METHOD_RESULT_H_

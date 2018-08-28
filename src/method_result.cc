#include "method_result.h"

namespace cpp_plugin {

MethodResult::MethodResult() {}

MethodResult::~MethodResult() {}

void MethodResult::Success(const void *result) { SuccessInternal(result); }

void MethodResult::Error(const std::string &error_code,
                         const std::string &error_message,
                         const void *error_details) {
  ErrorInternal(error_code, error_message, error_details);
}

void MethodResult::NotImplemented() { NotImplementedInternal(); }

}  // namespace cpp_plugin

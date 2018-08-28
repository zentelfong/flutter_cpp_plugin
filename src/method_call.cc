
#include "method_call.h"

namespace cpp_plugin {

MethodCall::MethodCall(const std::string &method_name)
    : method_name_(method_name) {}

MethodCall::~MethodCall() {}

}  // namespace cpp_plugin

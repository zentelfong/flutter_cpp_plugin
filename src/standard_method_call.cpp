#include "standard_method_call.h"

namespace cpp_plugin {

StandardMethodCall::StandardMethodCall(const std::string &method_name,
	std::unique_ptr<StandardValue> arguments)
	:MethodCall(method_name), arguments_(std::move(arguments))
{

}

StandardMethodCall::~StandardMethodCall()
{

}

const void *StandardMethodCall::arguments() const
{
	return &arguments_;
}

const StandardValue *StandardMethodCall::GetArgumentsAsValue() const
{
	return arguments_.get();
}


}//namesapce

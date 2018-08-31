#ifndef CPP_PLUGIN_STANDARD_METHOD_CALL_H_
#define CPP_PLUGIN_STANDARD_METHOD_CALL_H_

#include <string>
#include <memory>
#include "method_call.h"
#include "standard_value.h"

namespace cpp_plugin {

class StandardMethodCall : public MethodCall {
public:
	explicit StandardMethodCall(const std::string &method_name, 
		std::unique_ptr<StandardValue> arguments);
	~StandardMethodCall();

	// Prevent copying.
	StandardMethodCall(StandardMethodCall const &) = delete;
	StandardMethodCall &operator=(StandardMethodCall const &) = delete;

	// MethodCall:
	const void *arguments() const override;
	const StandardValue *GetArgumentsAsValue() const;

private:
	std::unique_ptr<StandardValue> arguments_;
};

}  // namespace cpp_plugin

#endif  // CPP_PLUGIN_STANDARD_METHOD_CALL_H_

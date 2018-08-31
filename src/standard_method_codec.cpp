#include "standard_method_codec.h"
#include "standard_value.h"
#include "standard_method_call.h"

namespace cpp_plugin {

const StandardMethodCodec &StandardMethodCodec::GetInstance() {
	static StandardMethodCodec sInstance;
	return sInstance;
}

std::unique_ptr<MethodCall> StandardMethodCodec::DecodeMethodCallInternal(
	const uint8_t *message, const size_t message_size) const {

	StandardValue method;
	size_t len = method.ReadValue(message,message_size);

	std::unique_ptr<StandardValue> arguments = std::make_unique<StandardValue>();
	arguments->ReadValue(message + len, message_size - len);

	return std::make_unique<StandardMethodCall>(*method.asString(), std::move(arguments));
}

std::unique_ptr<std::vector<uint8_t>> StandardMethodCodec::EncodeMethodCallInternal(
	const MethodCall &method_call) const {
	std::unique_ptr<std::vector<uint8_t>> data = std::make_unique<std::vector<uint8_t>>();
	data->push_back(0);
	StandardValue* pvalue = (StandardValue*)method_call.arguments();
	if (pvalue)
		pvalue->WriteValue(*data);
	return data;
}


std::unique_ptr<std::vector<uint8_t>> StandardMethodCodec::EncodeSuccessEnvelopeInternal(
	const void *result) const
{
	std::unique_ptr<std::vector<uint8_t>> data = std::make_unique<std::vector<uint8_t>>();
	data->push_back(0);

	StandardValue* pvalue = (StandardValue*)result;
	if (pvalue)
		pvalue->WriteValue(*data);

	return data;
}

std::unique_ptr<std::vector<uint8_t>> StandardMethodCodec::EncodeErrorEnvelopeInternal(
	const std::string &error_code, const std::string &error_message,
	const void *error_details) const {
	std::unique_ptr<std::vector<uint8_t>> data = std::make_unique<std::vector<uint8_t>>();
	data->push_back(1);

	StandardValue svalue;
	svalue.fromString(error_code);
	svalue.WriteValue(*data);

	svalue.fromString(error_message);
	svalue.WriteValue(*data);

	StandardValue* pvalue = (StandardValue*)error_details;
	if(pvalue)
		pvalue->WriteValue(*data);

	return data;
}


}//namespace



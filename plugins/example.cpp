#include "plugin_manager.h"
#include "json_plugin.h"
#include "standard_plugin.h"

using namespace cpp_plugin;

class TestPlugin:public JsonPlugin
{
public:
  TestPlugin()
    :JsonPlugin("cppplugins.flutter.io/json_plugin")
  {

  }

  virtual void HandleJsonMethodCall(const JsonMethodCall &method_call,
        std::unique_ptr<MethodResult> result)
  {
    if(method_call.method_name() == "testString")
    {
      auto argument = method_call.GetArgumentsAsJson().asString();
      Json::Value value(argument);
      result->Success(&value);


      //调用dart
      InvokeMethod("testString",value);
    }
	else if (method_call.method_name() == "testInt")
	{
		auto argument = method_call.GetArgumentsAsJson().asInt();
		Json::Value value(argument + 1);
		result->Success(&value);

		//调用dart
		InvokeMethod("testInt", value);
	}
	else if (method_call.method_name() == "testDouble")
	{
		auto argument = method_call.GetArgumentsAsJson().asDouble();
		Json::Value value(argument + 1);
		result->Success(&value);

		//调用dart
		InvokeMethod("testDouble", value);
	}



  }
};


class TestStandardPlugin:public StandardPlugin
{
public:
	TestStandardPlugin()
	:StandardPlugin("cppplugins.flutter.io/standard_plugin")
	{

	}

	virtual void HandleStandardMethodCall(const StandardMethodCall &method_call,
									std::unique_ptr<MethodResult> result)
	{
		if(method_call.method_name() == "testString")
		{
			const StandardValue* argument = method_call.GetArgumentsAsValue();
			result->Success(argument);


			//调用dart
			std::unique_ptr<StandardValue> testValue = std::make_unique<StandardValue>();
			testValue->fromString(*argument->asString());
			InvokeMethod("testString", std::move(testValue));
		}
		else if (method_call.method_name() == "testInt")
		{
			const StandardValue* argument = method_call.GetArgumentsAsValue();

			StandardValue value;
			value.fromInt(argument->asInt()+1);
			result->Success(argument);

			//调用dart
			std::unique_ptr<StandardValue> testValue = std::make_unique<StandardValue>();
			testValue->fromInt(argument->asInt() + 1);
			InvokeMethod("testInt", std::move(testValue));
		}
		else if (method_call.method_name() == "testDouble")
		{
			const StandardValue* argument = method_call.GetArgumentsAsValue();

			StandardValue value;
			value.fromDouble(argument->asDouble() + 1);
			result->Success(argument);

			//调用dart
			std::unique_ptr<StandardValue> testValue = std::make_unique<StandardValue>();
			testValue->fromDouble(argument->asDouble() + 1);
			InvokeMethod("testDouble", std::move(testValue));
		}
	}

};




void plugin_main()
{
  PluginManager::Instance()->RegisterPlugin(new TestPlugin());
  PluginManager::Instance()->RegisterPlugin(new TestStandardPlugin());
}
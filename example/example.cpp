#include "plugin_manager.h"
#include "json_plugin.h"

using namespace cpp_plugin;

class TestPlugin:public JsonPlugin
{
public:
  TestPlugin()
    :JsonPlugin("cppplugins.flutter.io/test_plugin")
  {

  }

  virtual void HandleJsonMethodCall(const JsonMethodCall &method_call,
        std::unique_ptr<MethodResult> result)
  {
    if(method_call.method_name() == "hello")
    {
      Json::Value value("world");
      result->Success(&value);

      //调用dart
      InvokeMethod("test",value);
    }
  }
};


void plugin_main()
{
  PluginManager::Instance()->RegisterPlugin(new TestPlugin());

}
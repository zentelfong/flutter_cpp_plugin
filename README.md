# flutter_cpp_plugin

#### 项目介绍
使用C++编写flutter插件，支持android,ios平台。

#### 使用说明

在pubspec.yaml文件中添加 

```
flutter_cpp_plugin:
    path: flutter_cpp_plugin所在目录

```

将你的c++代码添加到plugins文件夹内。


#### 代码示例


C++代码

```C++

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
    if(method_call.method_name() == "hello")
    {
      Json::Value value=method_call.GetArgumentsAsJson();
      result->Success(&value);

      //调用dart
      InvokeMethod("hello",value);
    }
  }
};

```

dart代码

```dart

MethodChannel jsonChannel = MethodChannel('cppplugins.flutter.io/json_plugin',JSONMethodCodec());

jsonChannel.setMethodCallHandler((MethodCall call){
    print("call from cpp plugin method ${call.method} arguments ${call.arguments}");
});

final String strResult = await jsonChannel.invokeMethod('hello','world');
assert(strResult=="world");

```
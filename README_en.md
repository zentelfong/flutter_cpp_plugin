# flutter_cpp_plugin

#### Project Introduction:
Use C++ to write nuter plug-in, support android and ios platforms。

#### Instructions for use:

Instruction in the pubspec.yaml file. 

```
flutter_cpp_plugin:
    path: flutter_cpp_plugin Directory

```

Add your C++ code to plugins folder.


#### Code Example:


C++ Code:

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

      //transfer dart
      InvokeMethod("hello",value);
    }
  }
};

```

dart Code:

```dart

MethodChannel jsonChannel = MethodChannel('cppplugins.flutter.io/json_plugin',JSONMethodCodec());

jsonChannel.setMethodCallHandler((MethodCall call){
    print("call from cpp plugin method ${call.method} arguments ${call.arguments}");
});

final String strResult = await jsonChannel.invokeMethod('hello','world');
assert(strResult=="world");

```

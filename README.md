# flutter_cpp_plugin

#### 项目介绍
flutter直接和c++通讯插件

#### 软件架构
软件架构说明


#### 安装教程

1. xxxx
2. xxxx
3. xxxx

#### 使用说明

###### 安卓

1. 将android下的src/main/java文件夹拷贝到项目中的android/app/src/main/java目录下。
2. 进入android/jni目录下调用ndk-build编译库，你的c++/c代码可以添加到Android.mk一起编译。
3. 编译完成，将android/libs内所有文件拷贝到项目中android/app/src/main/jniLibs目录下。
4. 在MainActivity.java中添加
```
import io.flutter.cppplugin.CppPlugin;

onCreate函数中添加
CppPlugin.registerWith(this);

```

###### IOS

1. 暂无



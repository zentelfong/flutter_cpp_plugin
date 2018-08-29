package io.flutter.cpp_plugin;

import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;
import io.flutter.plugin.common.PluginRegistry.Registrar;
import java.nio.ByteBuffer;

public class CppPlugin{
  public static BinaryMessenger sMessenger;

  /** Plugin registration. */
  public static void registerWith(Registrar registrar) 
  {
    sMessenger=registrar.messenger();
  }

  public static void invokeMethodCall(String channel, ByteBuffer message)
  {
    sMessenger.send(channel,message);
  }

  //注册插件
  public static void registerPlugin(String channel)
  {
    BinaryMessageHandler handler=new CppBinaryMessageHandler(channel);
    sMessenger.setMessageHandler(channel,handler);
  }

  public static void unregisterPlugin(String channel)
  {
    sMessenger.setMessageHandler(channel,null);
  }

  /** Do not allow direct instantiation. */
  private CppPlugin() {}
}

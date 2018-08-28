package io.flutter.cpp_plugin;

import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;
import io.flutter.plugin.common.PluginRegistry.Registrar;
import java.nio.ByteBuffer;

public class CppPlugin{
  public static BinaryMessenger sMessenger;

	static {
		System.loadLibrary("cpp_plugin");
	}

  /** Plugin registration. */
  public static void registerWith(Registrar registrar) 
  {
    sMessenger=registrar.messenger();
  }

  public static void send(String channel, ByteBuffer message)
  {
    sMessenger.send(channel,message);
  }

  public static void send2(String channel,ByteBuffer message,long callbackId)
  {
    BinaryReply reply=new CppBinaryReply(callbackId);
    sMessenger.send(channel,message,reply);
  }  

  public static void setMessageHandler(String channel, long handlerid)
  {
    BinaryMessageHandler handler=new CppBinaryMessageHandler(handlerid);
    sMessenger.setMessageHandler(channel,handler);
  }

  /** Do not allow direct instantiation. */
  private CppPlugin() {}
}

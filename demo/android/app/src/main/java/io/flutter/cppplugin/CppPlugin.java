package io.flutter.cppplugin;

import io.flutter.plugin.common.PluginRegistry;
import io.flutter.plugin.common.PluginRegistry.Registrar;
import io.flutter.plugin.common.BinaryMessenger;
import io.flutter.plugin.common.BinaryMessenger.BinaryMessageHandler;
import java.nio.ByteBuffer;

public class CppPlugin{

	static {
		System.loadLibrary("flutter_cpp_plugin");
	}	

  public static BinaryMessenger sMessenger;

  /** Plugin registration. */
  public static void registerWith(PluginRegistry registry) {
    if (alreadyRegisteredWith(registry)) {
      return;
    }
  }

  private static boolean alreadyRegisteredWith(PluginRegistry registry) {
    final String key = CppPlugin.class.getCanonicalName();
    if (registry.hasPlugin(key)) {
      return true;
    }
    Registrar registrar = registry.registrarFor(key);
    sMessenger=registrar.messenger();
    mainJni();
    return false;
  }


  public static void invokeMethodCall(String channel,byte[] bytes)
  {
    final ByteBuffer buffer = ByteBuffer.allocateDirect(bytes.length);
    buffer.put(bytes);    
    sMessenger.send(channel,buffer);
  }


  public static void registerPlugin(String channel)
  {
    if(channel!=null)
    {
      BinaryMessageHandler handler=new CppBinaryMessageHandler(channel);
      sMessenger.setMessageHandler(channel,handler);
    }
  }

  public static void unregisterPlugin(String channel)
  {
    if(channel!=null)
      sMessenger.setMessageHandler(channel,null);
  }

  /** Do not allow direct instantiation. */
  private CppPlugin() {}

  public static native void mainJni();
}

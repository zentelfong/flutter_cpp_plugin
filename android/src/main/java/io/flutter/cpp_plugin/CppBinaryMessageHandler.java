package io.flutter.cpp_plugin;
import io.flutter.plugin.common.BinaryMessenger;

class CppBinaryMessageHandler extends BinaryMessenger.BinaryMessageHandler
{
    public CppBinaryMessageHandler(long object)
    {
        mObject=object;
    }
    

    public void onMessage(ByteBuffer message, BinaryReply reply);
    {
        onMessage_jni(message,reply);
    }
    
    public native void onMessage_jni(ByteBuffer message,BinaryReply reply);
    private final long mObject;
}

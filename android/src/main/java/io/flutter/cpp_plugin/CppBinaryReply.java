package io.flutter.cpp_plugin;
import io.flutter.plugin.common.BinaryMessenger.BinaryReply;

class CppBinaryReply extends BinaryReply
{
    public CppBinaryReply(long object)
    {
        mObject=object;
    }
    
    public void reply(ByteBuffer reply)
    {
        reply_jni(reply);
    }
    
    public native void reply_jni(ByteBuffer reply);
    private final long mObject;
}

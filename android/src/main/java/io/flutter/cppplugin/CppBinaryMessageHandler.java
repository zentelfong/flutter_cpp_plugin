package io.flutter.cppplugin;
import java.nio.ByteBuffer;
import io.flutter.plugin.common.BinaryMessenger;
import io.flutter.plugin.common.BinaryMessenger.BinaryReply;
import io.flutter.plugin.common.BinaryMessenger.BinaryMessageHandler;

class CppBinaryMessageHandler implements BinaryMessageHandler
{	
    public CppBinaryMessageHandler(String channel)
    {
        mChannel=channel;
    }
    
    public void onMessage(ByteBuffer message, BinaryReply reply)
    {
        onMessageJni(message,reply);
    }
    
    public native void onMessageJni(ByteBuffer message,BinaryReply reply);
    
    private final String mChannel;
}

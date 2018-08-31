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

    public ByteBuffer convertData(byte[] bytes) {
        final ByteBuffer buffer = ByteBuffer.allocateDirect(bytes.length);
        buffer.put(bytes);
        return buffer;
    }


    public void onMessage(ByteBuffer message, BinaryReply reply)
    {
        if(message.hasArray())
            onMessageJni(message.array(),reply);
        else
        {
            byte[] b = new byte[message.capacity()];
            message.get(b, 0, b.length);
            onMessageJni(b,reply);
        }
    }
    
    public native void onMessageJni(byte[] message,BinaryReply reply);
    
    private final String mChannel;
}

#pragma once
#include "Common.h"

namespace cpp_plugin
{

/**
 * Binary message reply callback. Used to submit a reply to an incoming
 * message from Flutter. Also used in the dual capacity to handle a reply
 * received from Flutter after sending a message.
 */
class BinaryReply {
    /**
     * Handles the specified reply.
     *
     * @param reply the reply payload, a direct-allocated {@link ByteBuffer} or null. Senders of
     * outgoing replies must place the reply bytes between position zero and current position.
     * Reply receivers can read from the buffer directly.
     */
    virtual void reply(const std::vector<uint8_t>& reply) =0;
};


/**
 * Handler for incoming binary messages from Flutter.
 */
class BinaryMessageHandler {
    /**
     * Handles the specified message.
     *
     * <p>Handler implementations must reply to all incoming messages, by submitting a single reply
     * message to the given {@link BinaryReply}. Failure to do so will result in lingering Flutter reply
     * handlers. The reply may be submitted asynchronously.</p>
     *
     * <p>Any uncaught exception thrown by this method will be caught by the messenger implementation and
     * logged, and a null reply message will be sent back to Flutter.</p>
     *
     * @param message the message {@link ByteBuffer} payload, possibly null.
     * @param reply A {@link BinaryReply} used for submitting a reply back to Flutter.
     */
    virtual void onMessage(const std::vector<uint8_t>& message, BinaryReply* reply) =0;
};



class BinaryMessenger {
    static BinaryMessenger* Instance();

    /**
     * Sends a binary message to the Flutter application.
     *
     * @param channel the name {@link String} of the logical channel used for the message.
     * @param message the message payload, a direct-allocated {@link ByteBuffer} with the message bytes
     * between position zero and current position, or null.
     */
    virtual void send(const std::string& channel,const std::vector<uint8_t>& message);

    /**
     * Sends a binary message to the Flutter application, optionally expecting a reply.
     *
     * <p>Any uncaught exception thrown by the reply callback will be caught and logged.</p>
     *
     * @param channel the name {@link String} of the logical channel used for the message.
     * @param message the message payload, a direct-allocated {@link ByteBuffer} with the message bytes
     * between position zero and current position, or null.
     * @param callback a {@link BinaryReply} callback invoked when the Flutter application responds to the
     * message, possibly null.
     */
    virtual void send(const std::string& channel, const std::vector<uint8_t>& message, BinaryReply* callback);

    /**
     * Registers a handler to be invoked when the Flutter application sends a message
     * to its host platform.
     *
     * <p>Registration overwrites any previous registration for the same channel name.
     * Use a null handler to deregister.</p>
     *
     * <p>If no handler has been registered for a particular channel, any incoming message on
     * that channel will be handled silently by sending a null reply.</p>
     *
     * @param channel the name {@link String} of the channel.
     * @param handler a {@link BinaryMessageHandler} to be invoked on incoming messages, or null.
     */
    virtual void setMessageHandler(const std::string& channel, BinaryMessageHandler* handler);

};


}//namespace
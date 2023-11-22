package carwash.serial;

import java.util.Optional;

/**
 * A communication channel.
 */
public interface Channel {

    /**
     * Sends a message through the channel.
     * @param message the message to send
     */
    void send(String message);

    /**
     * Receives a message from the channel.
     * @return the received message. {@code Optional.empty} if no message is present.
     */
    Optional<String> receive();

    /**
     * Closes the port on which the communication was established.
     */
    void closePort();

    /**
     * Retrieves the last error message.
     * @return a string containing the last error message
     */
    String getErrorMessage();

}

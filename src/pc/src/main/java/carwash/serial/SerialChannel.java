package carwash.serial;

import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

import java.nio.charset.StandardCharsets;
import java.util.Optional;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/**
 * A serial communication channel.
 */
@SuppressWarnings("PMD.AvoidStringBufferField")   // Buffer is cleared.
public class SerialChannel implements Channel, SerialPortEventListener {

    private final SerialPort port;
    private final StringBuffer messageBuffer = new StringBuffer();
    private final BlockingQueue<String> receivedMessages = new ArrayBlockingQueue<>(100);
    private String errorMessage;

    /**
     * Creates a new instance of a serial communication channel given the serial port and baud rate.
     * @param port the serial port on which the communication is established
     * @param baudRate the proper baud rate
     */
    @SuppressFBWarnings("MC_OVERRIDABLE_METHOD_CALL_IN_CONSTRUCTOR")
    public SerialChannel(final String port, final int baudRate) {
        this.port = new SerialPort(port);
        try {
            this.port.openPort();
            this.port.setParams(baudRate, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
            this.port.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT);
            this.port.addEventListener(this);
        } catch (final SerialPortException e) {
            errorMessage = e.getMessage();
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void send(final String message) {
        try {
            port.writeBytes(message.getBytes(StandardCharsets.UTF_8));
        } catch (final SerialPortException e) {
            errorMessage = e.getMessage();
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Optional<String> receive() {
        try {
            return Optional.of(receivedMessages.take());
        } catch (final InterruptedException e) {
            errorMessage = e.getMessage();
        }
        return Optional.empty();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void closePort() {
        final boolean closed;
        try {
            closed = port.closePort();
            if (!closed) {
                errorMessage = "Port could not be closed.";
            }
        } catch (final SerialPortException e) {
            errorMessage = e.getMessage();
        }
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public String getErrorMessage() {
        return errorMessage;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void serialEvent(final SerialPortEvent serialPortEvent) {
        if (!serialPortEvent.isRXCHAR()) {
            return;
        }
        try {
            final String received = port.readString(serialPortEvent.getEventValue())
                    .replaceAll("\r", "");
            messageBuffer.append(received);
            while (true) {
                final String currentMessage = messageBuffer.toString();
                final int indexOfLineFeed = currentMessage.indexOf('\n');
                if (indexOfLineFeed >= 0) {
                    receivedMessages.add(currentMessage.substring(0, indexOfLineFeed));
//                    messageBuffer = new StringBuffer();
                    messageBuffer.setLength(0);
                    if (indexOfLineFeed + 1 < currentMessage.length()) {
                        messageBuffer.append(currentMessage.substring(indexOfLineFeed + 1));
                    }
                } else {
                    break;
                }
            }
        } catch (final SerialPortException e) {
            errorMessage = e.getMessage();
        }
    }

}

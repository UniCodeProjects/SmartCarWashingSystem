package carwash;

import carwash.controllers.ViewUpdater;
import carwash.serial.SerialChannel;
import javafx.application.Application;
import javafx.scene.paint.Color;
import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortList;

import java.util.Objects;

/**
 * The startup class of this project.
 */
public final class App {

    private static volatile boolean isProgramRunning = true;

    private App() { }

    /**
     * Application entry-point.
     * @param args arguments
     */
    public static void main(final String[] args) {
        String port = "";
        for (final String currentPortName : SerialPortList.getPortNames()) {
            System.out.println(currentPortName);
            SerialPort testPort = new SerialPort(currentPortName);
            try {
                if (testPort.isOpened()) {
                    continue;
                }
                testPort.openPort();
                String received = testPort.readString();
                if (Objects.nonNull(received) && received.contains("HELLO JAVA")) {
                    port = currentPortName;
                    testPort.closePort();
                }
            } catch (SerialPortException e) {

            }
        }
        System.out.println(port);
        final SerialChannel channel = new SerialChannel(Objects.requireNonNull(port), SerialPort.BAUDRATE_9600);
        final Thread serialChannelThread = new Thread(() -> {
            while (isProgramRunning) {
                final String s = channel.receive().orElse("");
                ViewUpdater.getInstance().getController().updateLogWindow(s);
                ViewUpdater.getInstance().getController().updateStatusCircleColour(Color.GREEN);
                // CHECKSTYLE: MagicNumber OFF
                ViewUpdater.getInstance().getController().updateNumWashes(12);
                ViewUpdater.getInstance().getController().updateTemperature(70);
                // CHECKSTYLE: MagicNumber ON
            }
        });
        serialChannelThread.start();
        Application.launch(Gui.class, args);
        channel.closePort();
        isProgramRunning = false;
        serialChannelThread.interrupt();
    }
}

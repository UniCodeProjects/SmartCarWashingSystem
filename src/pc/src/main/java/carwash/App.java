package carwash;

import carwash.controllers.Controller;
import carwash.controllers.ControllerImpl;
import carwash.controllers.ViewUpdater;
import carwash.serial.PortUtils;
import carwash.serial.SerialChannel;
import javafx.application.Application;
import jssc.SerialPort;

/**
 * The startup class of this project.
 */
public final class App {

    private static volatile boolean isProgramRunning = true;
    private static volatile boolean isControllerSet;
    private static final SerialChannel CHANNEL = new SerialChannel(PortUtils.getUsedPort(), SerialPort.BAUDRATE_9600);
    private static final Controller CONTROLLER = new ControllerImpl(CHANNEL);
    private static final Thread SERIAL_CHANNEL_LISTENER = new Thread(() -> {
        while (isProgramRunning) {
            if (!isControllerSet) {
                ViewUpdater.getInstance().getController().setController(CONTROLLER);
                isControllerSet = true;
            }
            final String s = CHANNEL.receive().orElse("");
            if (s.contains("temp")) {
                ViewUpdater.getInstance().getController().updateTemperature(Double.parseDouble(s.replace("temp: ", "")));
            } else if (s.contains("washed cars")) {
                ViewUpdater.getInstance().getController().updateNumWashes(Integer.parseInt(s.replace("washed cars: ", "")));
            } else {
                ViewUpdater.getInstance().getController().updateLogWindow(s);
            }
        }
    });

    private App() { }

    /**
     * Application entry-point.
     * @param args arguments
     */
    public static void main(final String[] args) {
        Application.launch(Gui.class, args);
        CHANNEL.closePort();
        isProgramRunning = false;
        SERIAL_CHANNEL_LISTENER.interrupt();
    }

    /**
     * Starts the serial channel listener thread.
     */
    public static void startSerialChannelListener() {
        SERIAL_CHANNEL_LISTENER.start();
    }

}

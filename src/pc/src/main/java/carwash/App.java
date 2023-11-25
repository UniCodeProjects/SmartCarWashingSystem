package carwash;

import carwash.controllers.ViewUpdater;
import carwash.serial.SerialChannel;
import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;
import javafx.application.Application;
import javafx.scene.paint.Color;
import jssc.SerialPort;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Objects;

/**
 * The startup class of this project.
 */
public final class App {

    private static volatile boolean isProgramRunning = true;
    private static final SerialChannel CHANNEL = new SerialChannel(getUsedPort(), SerialPort.BAUDRATE_9600);
    /**
     * Sample thread.
     */
    public static final Thread SERIAL_CHANNEL_THREAD = new Thread(() -> {
        // TODO: Example code, remove.
        while (isProgramRunning) {
            final String s = CHANNEL.receive().orElse("");
            ViewUpdater.getInstance().getController().updateLogWindow(s);
            ViewUpdater.getInstance().getController().updateStatusCircleColour(Color.GREEN);
            // CHECKSTYLE: MagicNumber OFF
            ViewUpdater.getInstance().getController().updateNumWashes(12);
            ViewUpdater.getInstance().getController().updateTemperature(70);
            // CHECKSTYLE: MagicNumber ON
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
        SERIAL_CHANNEL_THREAD.interrupt();
    }

    @SuppressWarnings("PMD.AssignmentInOperand")
    @SuppressFBWarnings(value = "DM_EXIT", justification = "Appropriate case")
    private static String getUsedPort() {
        String port = null;
        String output;
        try {
            final String scriptPath = new File("src/main/resources/port_finder.py").getAbsolutePath();
            final Process process = Runtime.getRuntime().exec("python " + scriptPath);
            try (BufferedReader stdOutput = new BufferedReader(new InputStreamReader(process.getInputStream(),
                    StandardCharsets.UTF_8))) {
                while ((output = stdOutput.readLine()) != null) {
                    port = output;
                }
            }
        } catch (final IOException e) {
            System.exit(-1);
        }
        if (Objects.isNull(port)) {
            Application.launch(ErrorScreen.class);
            System.exit(0);
        }
        return port;
    }

}

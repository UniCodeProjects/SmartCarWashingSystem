package carwash.serial;

import carwash.ErrorScreen;
import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;
import javafx.application.Application;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Objects;

/**
 * Utility class for ports.
 */
public final class PortUtils {

    private PortUtils() { }

    /**
     * Retrieves the USB port in which Arduino is plugged in.
     * @return the USB port as a string.
     */
    @SuppressWarnings("PMD.AssignmentInOperand")
    @SuppressFBWarnings(value = "DM_EXIT", justification = "Appropriate case")
    public static String getUsedPort() {
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

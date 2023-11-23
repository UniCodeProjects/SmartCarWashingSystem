package carwash;

import javafx.application.Application;
import javafx.scene.control.Alert;
import javafx.stage.Stage;

/**
 * This GUI entrance point is only launched when Arduino is not connected to any port.
 */
public final class ErrorScreen extends Application {

    /**
     * {@inheritDoc}
     */
    @Override
    public void start(final Stage primaryStage) {
        final Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Arduino Uno is not connected.");
        alert.setHeaderText("Error!");
        alert.setContentText("Arduino Uno was not found on any serial port, please try again.");
        alert.show();
    }

}

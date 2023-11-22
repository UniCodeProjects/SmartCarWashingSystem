package carwash.controllers;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

import java.net.URL;
import java.util.ResourceBundle;

/**
 * The FXML controller for the view.
 */
public class ViewController implements Initializable {

    // CHECKSTYLE: MagicNumber OFF
    private static final String DEG_SYMBOL = String.valueOf(Character.toChars(0x00B0)[0]);
    // CHECKSTYLE: MagicNumber ON
    private static final String CELSIUS = DEG_SYMBOL + "C";
    @FXML
    private TextArea logWindow;
    @FXML
    private Button maintenanceBtn;
    @FXML
    private Label numWashes;
    @FXML
    private Circle statusCircle;
    @FXML
    private Label temperature;
    private String numWashesDefaultText;
    private String temperatureDefaultText;

    /**
     * The event handler for when the maintenance button is pressed.
     * @param event the event
     */
    @FXML
    void onMaintenanceDone(final ActionEvent event) {

    }

    /**
     * Updates the log window with the specified text.
     * @param text the text to show in the log window
     */
    public void updateLogWindow(final String text) {
        Platform.runLater(() -> logWindow.setText(text));
    }

    /**
     * Updates the amount of completed washes.
     * @param amount the new amount
     */
    public void updateNumWashes(final int amount) {
        Platform.runLater(() -> numWashes.setText(numWashesDefaultText + " " + amount));
    }

    /**
     * Updates the status circle colour.
     * @param color the new colour
     */
    public void updateStatusCircleColour(final Color color) {
        Platform.runLater(() -> statusCircle.setFill(color));
    }

    /**
     * Updates the current temperature value.
     * @param temperature the new temperature
     */
    public void updateTemperature(final int temperature) {
        Platform.runLater(() -> this.temperature.setText(temperatureDefaultText + " " + temperature + CELSIUS));
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void initialize(final URL location, final ResourceBundle resources) {
        numWashesDefaultText = numWashes.getText();
        temperatureDefaultText = temperature.getText();
    }

}

package carwash;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.shape.Circle;

/**
 * The FXML controller for the view.
 */
public class ViewController {

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

    /**
     * The event handler for when the maintenance button is pressed.
     * @param event the event
     */
    @FXML
    void onMaintenanceDone(final ActionEvent event) {

    }

}

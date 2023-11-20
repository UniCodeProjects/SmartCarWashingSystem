package carwash;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * View main class.
 */
public final class Gui extends Application {

    private static final double MIN_HEIGHT = 450;
    private static final double MIN_WIDTH = 600;

    /**
     * {@inheritDoc}
     */
    @Override
    public void start(final Stage stage) throws Exception {
        final Parent root = FXMLLoader.load(ClassLoader.getSystemResource("layouts/carwash.fxml"));
        stage.setScene(new Scene(root));
        stage.setMinHeight(MIN_HEIGHT);
        stage.setMinWidth(MIN_WIDTH);
        stage.setTitle("Smart Car Wash");
        stage.show();
    }
}

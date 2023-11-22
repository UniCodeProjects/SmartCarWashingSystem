package carwash;

import carwash.controllers.ViewController;
import carwash.controllers.ViewUpdater;
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
        final FXMLLoader loader = new FXMLLoader(ClassLoader.getSystemResource("layouts/carwash.fxml"));
        final Parent root = loader.load();
        final ViewController controller = loader.getController();
        ViewUpdater.getInstance().attachController(controller);
        stage.setScene(new Scene(root));
        stage.setMinHeight(MIN_HEIGHT);
        stage.setMinWidth(MIN_WIDTH);
        stage.setTitle("Smart Car Wash");
        stage.show();
    }
}

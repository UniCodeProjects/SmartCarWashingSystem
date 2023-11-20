package carwash;

import javafx.application.Application;

/**
 * The startup class of this project.
 */
public final class App {

    private App() { }

    /**
     * Application entry-point.
     * @param args arguments
     */
    public static void main(final String[] args) {
        Application.launch(Gui.class, args);
    }
}
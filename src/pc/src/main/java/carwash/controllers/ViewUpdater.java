package carwash.controllers;

import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;

import java.util.Objects;

/**
 * A singleton used to update the GUI while interacting with multiple threads.
 */
public final class ViewUpdater {

    private ViewController controller;

    private ViewUpdater() {
    }

    // Making the singleton thread safe.
    private static class LazyHolder {
        static final ViewUpdater INSTANCE = new ViewUpdater();
    }

    /**
     * Retrieves the single instance of this object.
     * @return the single instance
     */
    public static ViewUpdater getInstance() {
        return LazyHolder.INSTANCE;
    }

    /**
     * Attaches the view controller to the view updater.
     * This allows to access the methods of the view controller designated to update the GUI.
     * @param controller the view controller
     */
    @SuppressFBWarnings("EI_EXPOSE_REP")
    public void attachController(final ViewController controller) {
        this.controller = controller;
    }

    /**
     * Retrieves the attached view controller.
     * @return the view controller
     */
    public ViewController getController() {
        return Objects.requireNonNull(controller);
    }

}

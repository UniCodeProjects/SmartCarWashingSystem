package carwash.controllers;

/**
 * The MVC controller.
 */
public interface Controller {

    /**
     * Signals to Arduino that the "maintenance done" button has been pressed on the GUI.
     */
    void maintenanceDone();
}

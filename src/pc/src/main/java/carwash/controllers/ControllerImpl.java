package carwash.controllers;

import carwash.serial.Channel;

/**
 * Default implementation of MVC controller.
 */
public class ControllerImpl implements Controller {
    private final Channel serialChannel;

    /**
     * Default constructor.
     * @param serialChannel the {@link Channel} used by the Java application and Arduino to communicate.
     */
    public ControllerImpl(final Channel serialChannel) {
        this.serialChannel = serialChannel;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void maintenanceDone() {
        serialChannel.send("Maintenance done");
    }
}

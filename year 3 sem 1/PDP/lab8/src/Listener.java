import mpi.MPI;

public class Listener implements Runnable {
    private final DSM dsm;

    public Listener(final DSM dsm) {
        this.dsm = dsm;
    }

    @Override
    public void run() {
        while (dsm.isActive()) {
            final Object[] messageBuffer = new Object[1];
            MPI.COMM_WORLD.Recv(messageBuffer, 0, 1, MPI.OBJECT, MPI.ANY_SOURCE, MPI.ANY_TAG);

            final Message message = (Message) messageBuffer[0];
            handleIncomingMessage(message);
        }
    }

    private void handleIncomingMessage(final Message message) {
        switch (message.getType()) {
            case SUBSCRIBE -> dsm.syncSubscription(message.getVariable(), message.getRank(), message.getTimestamp());
            case UPDATE -> dsm.updateLocalVariable(message.getVariable(), message.getValue(), message.getRank(), message.getTimestamp());
            case QUIT -> dsm.finalize(message.getRank(), message.getTimestamp());
            default -> System.err.println("Unexpected message type: " + message.getType());
        }
    }
}

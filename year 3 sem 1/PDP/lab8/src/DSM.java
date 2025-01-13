import mpi.MPI;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class DSM {
    private final Map<String, Object> variables;
    private final Map<String, Set<Integer>> subscribers;
    private final int rank = MPI.COMM_WORLD.Rank();
    private final int[] counter;
    private volatile boolean active = true;

    public DSM() {
        this.variables = new ConcurrentHashMap<>();
        this.subscribers = new ConcurrentHashMap<>();
        this.counter = new int[MPI.COMM_WORLD.Size()];

        counter[rank] = 1;
        log("Started DSM for process " + rank);
    }

    public void initializeVariables(String... vars) {
        for (String var : vars) {
            variables.put(var, 0);
            subscribers.put(var, new HashSet<>());
        }
    }

    public void subscribe(final String variable) {
        if (!variables.containsKey(variable)) {
            logError("Cannot subscribe to unknown variable: " + variable);
            return;
        }
        subscribers.get(variable).add(rank);
        incrementCounter();
        log("Subscribed to variable '" + variable + "'");

        sendToAll(Message.subscribeMessage(variable, rank, counter));
    }

    public void syncSubscription(final String variable, final int rank, final int[] rankCounter) {
        subscribers.get(variable).add(rank);
        incrementCounter();
        mergeCounter(rankCounter);
        log("Synchronized subscription for variable '" + variable + "' from process " + rank);
    }

    public synchronized void updateVariable(final String variable, final Integer value) {
        if (!subscribers.get(variable).contains(rank)) {
            logError("Cannot update variable '" + variable + "'. Not subscribed.");
            return;
        }
        updateLocalVariable(variable, value, rank, counter);
        incrementCounter();
        log("Updated variable '" + variable + "' to " + value);

        sendToSubscribers(variable, Message.updateMessage(variable, value, rank, counter));
    }

    public synchronized void compareAndExchange(final String variable, final Integer oldValue, final Integer newValue) {
        if (!variables.containsKey(variable)) {
            logError("Unknown variable: " + variable);
            return;
        }
        if (Objects.equals(variables.get(variable), oldValue)) {
            updateVariable(variable, newValue);
        } else {
            log("CompareAndExchange failed for variable '" + variable + "'. Current value: " + variables.get(variable));
        }
    }

    public synchronized void updateLocalVariable(final String variable, final Integer value, final Integer senderRank, final int[] rankCounter) {
        if (!variables.containsKey(variable)) {
            logError("Unknown variable: " + variable);
            return;
        }
        if (senderRank != rank) {
            incrementCounter();
            mergeCounter(rankCounter);
            log("Received update for variable '" + variable + "' from process " + senderRank);
        }
        variables.put(variable, value);
    }

    private void sendToSubscribers(final String variable, final Message message) {
        subscribers.get(variable).stream()
                .filter(subscriber -> subscriber != rank)
                .forEach(subscriber -> sendMessage(message, subscriber));
    }

    private void sendToAll(final Message message) {
        for (int i = 0; i < MPI.COMM_WORLD.Size(); i++) {
            if (i != rank || message.getType().equals(Message.Type.QUIT)) {
                sendMessage(message, i);
            }
        }
    }

    private void sendMessage(final Message message, final int destination) {
        MPI.COMM_WORLD.Send(new Object[]{message}, 0, 1, MPI.OBJECT, destination, 0);
    }

    private void incrementCounter() {
        counter[rank]++;
    }

    private void mergeCounter(final int[] otherCounter) {
        for (int i = 0; i < counter.length; i++) {
            counter[i] = Math.max(counter[i], otherCounter[i]);
        }
    }

    public void close() {
        active = false;
        incrementCounter();
        log("Closing DSM.");
        sendToAll(Message.quitMessage(rank, counter));
    }

    public void finalize(int senderRank, int[] timestamp) {
        incrementCounter();
        mergeCounter(timestamp);
        log("Received QUIT message from process " + senderRank);
    }

    public boolean isActive() {
        return active;
    }

    private void log(String message) {
        System.out.printf("%s [Process %d]: %s%n", getTimestamp(), rank, message);
    }

    private void logError(String message) {
        System.err.printf("%s [Process %d]: ERROR - %s%n", getTimestamp(), rank, message);
    }

    private String getTimestamp() {
        return Arrays.toString(counter);
    }
}

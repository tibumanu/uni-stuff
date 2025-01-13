//package Threads;
//
//import java.util.*;
//import java.util.concurrent.*;
//import java.util.concurrent.atomic.AtomicInteger;
//import java.util.concurrent.locks.Lock;
//import java.util.concurrent.locks.ReentrantLock;
//
//public class GraphColoring {
//    public static Map<Integer, String> getColoredGraph(int threadsNumber, Graph graph, Colors colors) {
//        // Initialize shared data structures
//        Vector<Integer> codes = new Vector<>();
//        int codesNumber = colors.getColorsNumber();
//        Vector<Integer> partialCodes = new Vector<>(Collections.nCopies(graph.getNodesNumber(), 0));
//        Lock lock = new ReentrantLock();
//
//        // Start the recursive graph coloring
//        ExecutorService executor = Executors.newFixedThreadPool(threadsNumber);
//        AtomicInteger availableThreads = new AtomicInteger(threadsNumber);
//
//        executor.submit(() -> getColoredGraphRecursive(availableThreads, 0, graph, codesNumber, partialCodes, lock, codes, executor));
//
//        // Wait for all threads to finish
//        executor.shutdown();
//        try {
//            if (!executor.awaitTermination(1, TimeUnit.HOURS)) {
//                throw new RuntimeException("Timeout waiting for threads to finish");
//            }
//        } catch (InterruptedException e) {
//            throw new RuntimeException("Thread execution interrupted", e);
//        }
//
//        // No solution found
//        if (codes.isEmpty()) {
//            return Collections.emptyMap();
//        }
//
//        // Solution found
//        return colors.getColorsForCodes(codes);
//    }
//
//    private static void getColoredGraphRecursive(
//            AtomicInteger threadsNumber,
//            int nodeId,
//            Graph graph,
//            int codesNumber,
//            Vector<Integer> partialCodes,
//            Lock lock,
//            Vector<Integer> codes,
//            ExecutorService executor) {
//
//        if (!codes.isEmpty()) {
//            return;
//        }
//
//        if (nodeId + 1 == graph.getNodesNumber()) {
//            if (isColorValid(nodeId, partialCodes, graph)) {
//                lock.lock();
//                try {
//                    if (codes.isEmpty()) {
//                        codes.addAll(partialCodes);
//                        System.out.println("Valid solution found: " + partialCodes);
//                    }
//                } finally {
//                    lock.unlock();
//                }
//            }
//            return;
//        }
//
//        int nextNode = nodeId + 1;
//        List<Future<?>> futures = new ArrayList<>();
//        List<Integer> validColors = new ArrayList<>();
//
//        for (int code = 0; code < codesNumber; code++) {
//            partialCodes.set(nextNode, code);
//            if (isColorValid(nextNode, partialCodes, graph)) {
//                if (threadsNumber.getAndDecrement() > 0) {
//                    Vector<Integer> nextPartialCodes = new Vector<>(partialCodes);
//                    Future<?> future = executor.submit(() ->
//                            getColoredGraphRecursive(threadsNumber, nextNode, graph, codesNumber, nextPartialCodes, lock, codes, executor)
//                    );
//                    futures.add(future);
//                } else {
//                    validColors.add(code);
//                }
//            }
//        }
//
//        for (Future<?> future : futures) {
//            try {
//                future.get();
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//        }
//
//        for (int code : validColors) {
//            partialCodes.set(nextNode, code);
//            Vector<Integer> nextPartialCodes = new Vector<>(partialCodes);
//            getColoredGraphRecursive(threadsNumber, nextNode, graph, codesNumber, nextPartialCodes, lock, codes, executor);
//        }
//    }
//
//
//
//    //verify if two neighbors have the same
////    private static boolean isColorValid(int node, Vector<Integer> codes, Graph graph){
////        for(int current=0; current < node; current++){
////            if((graph.existsEdge(node,current) || graph.existsEdge(current,node)) && codes.get(node) == codes.get(current).intValue()){
////                return false;
////            }
////        }
////        return true;
////    }
//    private static boolean isColorValid(int node, Vector<Integer> codes, Graph graph) {
//        for (int neighbor : graph.getNodes().get(node)) { // Iterate over all neighbors of 'node'
//            if (neighbor < codes.size() && codes.get(neighbor).intValue() == codes.get(node).intValue()) {
//                return false; // Return false if any neighbor has the same color
//            }
//        }
//        return true;
//    }
//
//}

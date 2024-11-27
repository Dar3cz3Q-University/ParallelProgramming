package src.zad_2;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        double xp = 0;
        double xk = Math.PI;
        double dx = 0.000001;

        final int THREADS = 4;
        final int TASKS = 50;

        double interval = (xk - xp) / (double) TASKS;

        ExecutorService executor = Executors.newFixedThreadPool(THREADS);
        List<Future<Double>> results = new ArrayList<>();
        for (int i = 0; i < TASKS; i++) {
            double start = xp + i * interval;
            double end = start + interval;
            Calka_callable worker = new Calka_callable(start, end, dx);
            results.add(executor.submit(worker));
        }

        double totalResult = 0;
        for (Future<Double> result : results) {
            try {
                totalResult += result.get();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        executor.shutdown();
        System.out.println(totalResult);
    }
}

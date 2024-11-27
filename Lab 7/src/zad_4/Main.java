package src.zad_4;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

    public static void main(String[] args) {
        double xp = 0;
        double xk = Math.PI;
        double dx = 0.000001;

        final int THREADS = 4;
        final int TASKS = 50;

        double interval = (xk - xp) / (double) TASKS;

        ExecutorService executor = Executors.newFixedThreadPool(THREADS);

        Result result = new Result();
        for (int i = 0; i < TASKS; i++) {
            double start = xp + i * interval;
            double end = start + interval;
            Calka_runnable calka_runnable = new Calka_runnable(start, end, dx, result);
            executor.execute(calka_runnable);
        }

        executor.shutdown();

        while (!executor.isTerminated()) {
        }

        System.out.println(result.get_result());
    }
}

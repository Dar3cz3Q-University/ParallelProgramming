package src.variant_3;

import src.Obraz;

public class Watek implements Runnable {
    private final int start;
    private final int step;
    private final Obraz obraz;

    Watek(int start, int step, Obraz obraz) {
        this.start = start;
        this.step = step;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_parallel_with_step(start, step);
    }

}

package src.variant_2;

import src.Obraz;

public class Watek implements Runnable {
    private final int start;
    private final int end;
    private final Obraz obraz;

    Watek(int start, int end, Obraz obraz) {
        this.start = start;
        this.end = end;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_parallel(start, end);
        obraz.print_histogram_parallel(start, end);
    }

}

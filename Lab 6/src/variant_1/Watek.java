package src.variant_1;

import src.Obraz;

public class Watek extends Thread {
    private final char znak;
    private final Obraz obraz;

    Watek(char znak, Obraz obraz) {
        this.znak = znak;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_parallel(znak);
        obraz.print_histogram_parallel(znak);
    }

}

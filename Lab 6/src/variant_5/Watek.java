package src.variant_5;

import src.Obraz;

public class Watek implements Runnable {
    private final int startRow;
    private final int endRow;
    private final int startCol;
    private final int endCol;
    private final Obraz obraz;

    Watek(int startRow, int endRow, int startCol, int endCol, Obraz obraz) {
        this.startRow = startRow;
        this.endRow = endRow;
        this.startCol = startCol;
        this.endCol = endCol;
        this.obraz = obraz;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_parallel(startRow, endRow, startCol, endCol);
    }

}

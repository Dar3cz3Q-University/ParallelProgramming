package src.zad_5;

import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class Histogram_test {

	public static void main(String[] args) {
		final int THREADS = 4;
		final int TASKS = 50;

		Scanner scanner = new Scanner(System.in);

		System.out.println("Set image size: n (#rows), m(#kolumns)");
		int n = scanner.nextInt();
		int m = scanner.nextInt();

		System.out.println("Set number of characters (max 94):");
		int charCount = scanner.nextInt();
		charCount = charCount > 94 ? 94 : charCount;

		scanner.close();

		Obraz obraz = new Obraz(n, m, charCount);

		obraz.calculate_histogram();
		obraz.print_histogram();

		int rowCountPerThread = (int) Math.ceil((double) n / (double) TASKS);
		int colCountPerThread = (int) Math.ceil((double) m / (double) TASKS);

		ExecutorService executor = Executors.newFixedThreadPool(THREADS);

		for (int i = 0; i < TASKS; i++) {
			for (int j = 0; j < TASKS; j++) {
				int startRow = i * rowCountPerThread;
				int endRow = (i == TASKS - 1) ? n : (i + 1) * rowCountPerThread;
				int startCol = j * colCountPerThread;
				int endCol = (j == TASKS - 1) ? m : (j + 1) * colCountPerThread;
				Runnable task = new Watek(startRow, endRow, startCol, endCol, obraz);
				executor.submit(task);
			}
		}

		executor.shutdown();

		while (!executor.isTerminated()) {
		}

		obraz.print_parallel_histogram();
		obraz.compareHistograms();
	}
}

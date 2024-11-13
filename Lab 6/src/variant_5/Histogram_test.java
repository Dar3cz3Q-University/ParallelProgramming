package src.variant_5;

import java.util.Scanner;

import src.Obraz;

class Histogram_test {

	public static void main(String[] args) {

		Scanner scanner = new Scanner(System.in);

		System.out.println("Set image size: n (#rows), m(#kolumns)");
		int n = scanner.nextInt();
		int m = scanner.nextInt();

		System.out.println("Set number of characters (max 94):");
		int charCount = scanner.nextInt();
		charCount = charCount > 94 ? 94 : charCount;

		System.out.println("Set number of threads (max " + m + "):");
		int threadCount = scanner.nextInt();
		threadCount = threadCount > m ? m : threadCount;

		scanner.close();

		Obraz obraz = new Obraz(n, m, charCount);

		obraz.calculate_histogram();
		obraz.print_histogram();

		int rowCountPerThread = (int) Math.ceil((double) n / (double) threadCount);
		int colCountPerThread = (int) Math.ceil((double) m / (double) threadCount);

		Thread[] NewThr = new Thread[threadCount];
		for (int i = 0; i < threadCount; i++) {
			for (int j = 0; j < threadCount; j++) {
				int startRow = i * rowCountPerThread;
				int endRow = (i == threadCount - 1) ? n : (i + 1) * rowCountPerThread;
				int startCol = j * colCountPerThread;
				int endCol = (j == threadCount - 1) ? m : (j + 1) * colCountPerThread;
				NewThr[i] = new Thread(new Watek(startRow, endRow, startCol, endCol, obraz));
				NewThr[i].start();
			}
		}

		for (int i = 0; i < threadCount; i++) {
			try {
				NewThr[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		obraz.print_parallel_histogram();
		obraz.compareHistograms();
	}
}

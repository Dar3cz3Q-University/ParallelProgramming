package src.variant_2;

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

		System.out.println("Set number of threads (max " + charCount + "):");
		int threadCount = scanner.nextInt();
		threadCount = threadCount > charCount ? charCount : threadCount;

		scanner.close();

		Obraz obraz = new Obraz(n, m, charCount);

		obraz.calculate_histogram();
		obraz.print_histogram();

		int charsPerThread = (int) Math.ceil((double) charCount / (double) threadCount);

		Thread[] NewThr = new Thread[threadCount];
		for (int i = 0; i < threadCount; i++) {
			int start = i * charsPerThread;
			int end = (i == threadCount - 1) ? charCount : (i + 1) * charsPerThread;
			NewThr[i] = new Thread(new Watek(start, end, obraz));
			NewThr[i].start();
		}

		for (int i = 0; i < threadCount; i++) {
			try {
				NewThr[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		obraz.compareHistograms();
	}
}
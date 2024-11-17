package src.variant_1;

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

		scanner.close();

		Obraz obraz = new Obraz(n, m, charCount);

		obraz.calculate_histogram();
		obraz.print_histogram();

		Watek[] NewThr = new Watek[charCount];

		for (int i = 0; i < charCount; i++) {
			(NewThr[i] = new Watek((char) (i + 33), obraz)).start();
		}

		for (int i = 0; i < charCount; i++) {
			try {
				NewThr[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		obraz.compareHistograms();
	}
}

package src.zad_5;

import java.util.Random;

public class Obraz {

	private int size_n;
	private int size_m;
	private char[][] tab;
	private char[] tab_symb;
	private int[] histogram;
	private int[] histogram_parallel;
	private int char_count;

	public Obraz(int n, int m, int charCount) {

		this.size_n = n;
		this.size_m = m;
		this.char_count = charCount;
		tab = new char[n][m];
		tab_symb = new char[char_count];

		final Random random = new Random();

		// for general case where symbols could be not just integers
		for (int k = 0; k < char_count; k++) {
			tab_symb[k] = (char) (k + 33); // substitute symbols
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				tab[i][j] = tab_symb[random.nextInt(char_count)]; // ascii 33-127
				// tab[i][j] = (char)(random.nextInt(94)+33); // ascii 33-127
				System.out.print(tab[i][j] + " ");
			}
			System.out.print("\n");
		}
		System.out.print("\n\n");

		histogram = new int[94];
		histogram_parallel = new int[char_count];
		clear_histogram();
	}

	public void clear_histogram() {
		for (int i = 0; i < char_count; i++) {
			histogram[i] = 0;
			histogram_parallel[i] = 0;
		}
	}

	public void calculate_histogram() {
		for (int i = 0; i < size_n; i++) {
			for (int j = 0; j < size_m; j++) {
				for (int k = 0; k < char_count; k++) {
					if (tab[i][j] == tab_symb[k])
						histogram[k]++;
				}
			}
		}
	}

	public void print_histogram() {
		System.out.println();
		for (int i = 0; i < char_count; i++)
			System.out.print(tab_symb[i] + " " + histogram[i] + "\n");
	}

	public void print_parallel_histogram() {
		System.out.println();
		for (int i = 0; i < char_count; i++)
			System.out.print(tab_symb[i] + " " + histogram_parallel[i] + "\n");
	}

	// Variant 1
	public void calculate_histogram_parallel(char znak) {
		for (int i = 0; i < size_n; i++) {
			for (int j = 0; j < size_m; j++) {
				if (tab[i][j] == znak)
					histogram_parallel[znak - 33]++;
			}
		}
	}

	public synchronized void print_histogram_parallel(char znak) {
		System.out.print("Thread " + Thread.currentThread().getId() + ": " + znak + " ");
		for (int i = 0; i < histogram_parallel[znak - 33]; i++) {
			System.out.print("=");
		}
		System.out.println();
	}

	// Variant 2
	public void calculate_histogram_parallel(int start, int end) {
		for (int i = 0; i < size_n; i++) {
			for (int j = 0; j < size_m; j++) {
				for (int k = start; k < end; k++) {
					if (tab[i][j] == tab_symb[k])
						histogram_parallel[k]++;
				}
			}
		}
	}

	public synchronized void print_histogram_parallel(int start, int end) {
		for (int i = start; i < end; i++) {
			System.out.print("Thread " + Thread.currentThread().getId() + ": " + tab_symb[i] + " ");
			for (int j = 0; j < histogram_parallel[i]; j++) {
				System.out.print("=");
			}
			System.out.println();
		}
	}

	// Variant 3
	public void calculate_histogram_parallel_with_step(int start, int step) {
		int[] histogram_local = new int[char_count];
		for (int i = start; i < size_n; i += step) {
			for (int j = 0; j < size_m; j++) {
				char symbol = tab[i][j];
				histogram_local[(int) symbol - 33]++;
			}
		}
		merge_histogram(histogram_local);
	}

	public synchronized void merge_histogram(int[] histogram_local) {
		for (int i = 0; i < char_count; i++) {
			histogram_parallel[i] += histogram_local[i];
		}
	}

	// Variant 4
	public void calculate_histogram_parallel_per_column(int start, int end) {
		int[] histogram_local = new int[char_count];
		for (int i = 0; i < size_n; i++) {
			for (int j = start; j < end; j++) {
				char symbol = tab[i][j];
				histogram_local[(int) symbol - 33]++;
			}
		}
		merge_histogram(histogram_local);
	}

	// Variant 5
	public void calculate_histogram_parallel(int startRow, int endRow, int startCol, int endCol) {
		int[] histogram_local = new int[char_count];
		for (int i = startRow; i < endRow; i++) {
			for (int j = startCol; j < endCol; ++j) {
				char symbol = tab[i][j];
				histogram_local[(int) symbol - 33]++;
			}
		}
		merge_histogram(histogram_local);
	}

	public void compareHistograms() {
		for (int i = 0; i < char_count; i++) {
			if (histogram[i] != histogram_parallel[i]) {
				System.out.println("Histograms are not the same!!!");
				return;
			}
		}
		System.out.println("Histograms are the same");
	}
}

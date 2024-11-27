package src.zad_1;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        double xp = 0;
        double xk = Math.PI;
        double dx = 0.000001;

        Scanner scanner = new Scanner(System.in);

        System.out.println("Podaj dx: ");

        dx = scanner.nextDouble();

        scanner.close();

        Calka calka = new Calka(xp, xk, dx);

        double wynik = calka.compute_integral();

        System.out.println("Wynik calki: " + wynik);
    }

}

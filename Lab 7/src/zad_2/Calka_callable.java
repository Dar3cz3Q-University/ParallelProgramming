package src.zad_2;

import src.zad_1.Calka;
import java.util.concurrent.Callable;

public class Calka_callable implements Callable<Double> {
	private final Calka _calka;

	public Calka_callable(double xp, double xk, double dx) {
		this._calka = new Calka(xp, xk, dx);
	}

	@Override
	public Double call() throws Exception {
		return _calka.compute_integral();
	}
}

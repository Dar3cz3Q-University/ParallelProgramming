package src.zad_4;

import src.zad_1.Calka;

public class Calka_runnable implements Runnable {
	private final Calka _calka;
	Result _result;

	public Calka_runnable(double xp, double xk, double dx, Result result) {
		this._calka = new Calka(xp, xk, dx);
		this._result = result;
	}

	@Override
	public void run() {
		_result.addToResult(_calka.compute_integral());
	}
}

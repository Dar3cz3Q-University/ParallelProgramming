package src.zad_4;

public class Result {
    private double _result = 0;

    public synchronized void addToResult(double data) {
        this._result += data;
    }

    public double get_result() {
        return this._result;
    }
}

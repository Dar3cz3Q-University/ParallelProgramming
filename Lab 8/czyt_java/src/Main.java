public class Main {
    public static void main(String[] args) {
        Czytelnia czytelnia = new Czytelnia();
        Thread[] pisarze = new Thread[5];
        Thread[] czytelnicy = new Thread[10];

        for (int i = 0; i < pisarze.length; i++) {
            pisarze[i] = new Thread(new Pisarz(czytelnia));
            pisarze[i].start();
        }

        for (int i = 0; i < czytelnicy.length; i++) {
            czytelnicy[i] = new Thread(new Czytelnik(czytelnia));
            czytelnicy[i].start();
        }

        for (Thread t : pisarze) {
            try {
                t.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        for (Thread t : czytelnicy) {
            try {
                t.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}

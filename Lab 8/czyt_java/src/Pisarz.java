class Pisarz implements Runnable {
    private final Czytelnia czytelnia;

    public Pisarz(Czytelnia czytelnia) {
        this.czytelnia = czytelnia;
    }

    @Override
    public void run() {
        try {
            while (true) {
                System.out.println("Pisarz " + Thread.currentThread().getId() + " - przed zamkiem");
                czytelnia.myWriteLockLock();

                System.out.println("Pisarz " + Thread.currentThread().getId() + " - wchodzę");
                pisze();

                System.out.println("Pisarz " + Thread.currentThread().getId() + " - wychodzę");
                czytelnia.myWriteLockUnlock();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void pisze() throws InterruptedException {
        System.out.println(
                "\t\tPiszę..." + "l_c: " + czytelnia.getLiczbaCzytelnikow() + " l_p: " + czytelnia.getLiczbaPisarzy());
        if (czytelnia.getLiczbaPisarzy() > 1
                || (czytelnia.getLiczbaPisarzy() == 1 && czytelnia.getLiczbaCzytelnikow() > 0)
                || czytelnia.getLiczbaCzytelnikow() < 0 || czytelnia.getLiczbaPisarzy() < 0) {
            System.exit(0);
        }
        Thread.sleep((long) (Math.random() * 2000));
    }
}

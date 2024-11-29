class Czytelnik implements Runnable {
    private final Czytelnia czytelnia;

    public Czytelnik(Czytelnia czytelnia) {
        this.czytelnia = czytelnia;
    }

    @Override
    public void run() {
        try {
            while (true) {
                System.out.println("Czytelnik " + Thread.currentThread().getId() + " - przed zamkiem");
                czytelnia.myReadLockLock();

                System.out.println("Czytelnik " + Thread.currentThread().getId() + " - wchodzę");
                czytam();

                System.out.println("Czytelnik " + Thread.currentThread().getId() + " - wychodzę");
                czytelnia.myReadLockUnlock();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void czytam() throws InterruptedException {
        System.out.println(
                "\t\tCzytam..." + "l_c: " + czytelnia.getLiczbaCzytelnikow() + " l_p: " + czytelnia.getLiczbaPisarzy());
        if (czytelnia.getLiczbaPisarzy() > 1
                || (czytelnia.getLiczbaPisarzy() == 1 && czytelnia.getLiczbaCzytelnikow() > 0)
                || czytelnia.getLiczbaCzytelnikow() < 0 || czytelnia.getLiczbaPisarzy() < 0) {
            System.exit(0);
        }
        Thread.sleep((long) (Math.random() * 2000));
    }
}

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

class Czytelnia {
    private int liczbaCzytelnikow = 0;
    private int liczbaPisarzy = 0;

    private final ReentrantLock lock = new ReentrantLock();
    private final Condition write = lock.newCondition();
    private final Condition read = lock.newCondition();

    public int getLiczbaCzytelnikow() {
        return liczbaCzytelnikow;
    }

    public int getLiczbaPisarzy() {
        return liczbaPisarzy;
    }

    public void myReadLockLock() throws InterruptedException {
        lock.lock();

        while (liczbaPisarzy > 0 || lock.hasWaiters(write)) {
            read.await();
        }

        liczbaCzytelnikow++;
        read.signalAll();
    }

    public void myReadLockUnlock() {
        liczbaCzytelnikow--;

        if (liczbaCzytelnikow == 0) {
            write.signal();
        }

        lock.unlock();
    }

    public void myWriteLockLock() throws InterruptedException {
        lock.lock();

        while (liczbaPisarzy > 0 || liczbaCzytelnikow > 0) {
            write.await();
        }

        liczbaPisarzy++;
    }

    public void myWriteLockUnlock() {
        liczbaPisarzy--;

        if (lock.hasWaiters(read)) {
            read.signalAll();
        } else {
            write.signal();
        }

        lock.unlock();
    }
}

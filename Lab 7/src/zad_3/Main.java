package src.zad_3;

import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;

public class Main {
    public static void main(String[] args) {
        int[] array = { 49, 78, 93, 9, 71, 54, 7, 90, 41, 19, 56, 17, 17, 67, 26, 75, 63, 6, 38, 6 };
        System.out.println("Tablica przed sortowaniem: " + Arrays.toString(array));

        ForkJoinPool pool = new ForkJoinPool();
        DivideTask task = new DivideTask(array);
        int[] sortedArray = pool.invoke(task);

        System.out.println("Tablica po sortowaniu: " + Arrays.toString(sortedArray));
    }
}

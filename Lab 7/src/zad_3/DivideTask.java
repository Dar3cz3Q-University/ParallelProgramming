package src.zad_3;

import java.util.Arrays;
import java.util.concurrent.RecursiveTask;

class DivideTask extends RecursiveTask<int[]> {

  private static final int THRESHOLD = 3;
  int[] arrayToDivide;

  public DivideTask(int[] arrayToDivide) {
    this.arrayToDivide = arrayToDivide;
  }

  @Override
  protected int[] compute() {

    if (arrayToDivide.length <= THRESHOLD) {
      Arrays.sort(arrayToDivide);
      return arrayToDivide;
    } else {
      int mid = arrayToDivide.length / 2;
      int[] left = Arrays.copyOfRange(arrayToDivide, 0, mid);
      int[] right = Arrays.copyOfRange(arrayToDivide, mid, arrayToDivide.length);

      DivideTask leftTask = new DivideTask(left);
      DivideTask rightTask = new DivideTask(right);

      leftTask.fork();
      rightTask.fork();

      int[] resultLeft = leftTask.join();
      int[] resultRight = rightTask.join();

      int[] result = new int[arrayToDivide.length];
      scal_tab(resultLeft, resultRight, result);

      return result;
    }
  }

  private void scal_tab(
      int[] tab1,
      int[] tab2,
      int[] scal_tab) {

    int i = 0, j = 0, k = 0;

    while ((i < tab1.length) && (j < tab2.length)) {

      if (tab1[i] < tab2[j]) {
        scal_tab[k] = tab1[i++];
      } else {
        scal_tab[k] = tab2[j++];
      }

      k++;
    }

    if (i == tab1.length) {

      for (int a = j; a < tab2.length; a++) {
        scal_tab[k++] = tab2[a];
      }

    } else {

      for (int a = i; a < tab1.length; a++) {
        scal_tab[k++] = tab1[a];
      }

    }
  }

}

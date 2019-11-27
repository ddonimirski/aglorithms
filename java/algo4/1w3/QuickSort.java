import java.lang.Comparable;
import edu.princeton.cs.algs4.StdOut;

class QuickSort {

    private static int partition(Comparable[] arr, int lo, int hi) {

        int i = lo, j = hi+1;
        Comparable pivot = arr[lo];
        while (true) {
            while (less(arr[++i], pivot))
                if (i == hi) break;
            while (less(pivot, arr[--j]))
                if (j == lo) break;

            if (i >= j) break;
            swap(arr, i , j);
        }
        swap(arr, lo, j);
        return j;
    }


    private static void sort(Comparable[] arr, int lo, int hi) {
        if (lo >= hi) return;
        int mid = partition(arr, lo, hi);
        sort(arr, lo, mid-1);
        sort(arr, mid+1, hi); 
    }


    public static void sort(Comparable[] arr) {
        sort(arr, 0, arr.length-1);
    }

    private static void pr(Integer[] arr) {
        for (Integer v: arr) {
            StdOut.print(v);
        }
        StdOut.println();
    }

    private static boolean less(Comparable a, Comparable b) {
        return a.compareTo(b) < 0;
    }

    private static void swap(Comparable[] arr, int i, int j) {
        if (i != j) {
            Comparable tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }




    public static void main(String[] args) {
        Integer[] arr = new Integer[] {2,5,6,8,9,4,1,3,7};
        pr(arr);
        sort(arr);
        pr(arr);
    }
}

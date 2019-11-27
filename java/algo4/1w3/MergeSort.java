import java.lang.Comparable;
import edu.princeton.cs.algs4.StdOut;

class MergeSort {
    private static void merge(Comparable[] arr, Comparable[] aux, int  lo, int mid, int hi)
    {
        //assert isSorted(arr, lo, mid): "should be sorted";
        //assert isSorted(arr, mid+1, hi): "should be sorted";

        // not neeeded -> swap arrays
        //for (int k = lo; k <= hi; ++k) {
        //    aux[k] = arr[k];
        //}

        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; ++k)
        {
            if (i > mid)                    arr[k] = aux[j++];
            else if (j > hi)                arr[k] = aux[i++];
            else if (less(aux[j], aux[i]))  arr[k] = aux[j++];
            else                            arr[k] = aux[i++];
        }
    }

    private static void sort(Comparable[] arr, Comparable[] aux, int lo, int hi) {
        //if (hi <= lo + CUTOFF - 1) {
        //    Insertion.sort(arr, lo, hi);
        //    return;
        //}
        if (hi <= lo) return;
        int mid = (lo + hi) / 2;
        sort(aux, arr, lo, mid);
        sort(aux, arr, mid+1, hi);
        if (!less(aux[mid+1], aux[mid])) return; //already sorted so we can skip merge
        merge(arr, aux, lo, mid, hi);
    }

    private static void sort(Comparable[] arr) {
        Comparable[] aux = new Comparable[arr.length];
        for (int i = 0; i < arr.length; i++) {
            aux[i] = arr[i];
        }

        sort(arr, aux, 0, arr.length-1);
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

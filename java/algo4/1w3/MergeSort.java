import java.util.Comparable;

class MergeSort {
    private static void merge(Comparable[] arr, Comparable[] aux, int  lo, int mid, int hi)
    {
        assert isSorted(arr, lo, mid): "should be sorted";
        assert isSorted(arr, mid+1, hi): "should be sorted";

        for (int k = lo; k <= hi; ++k) {
            aux[k] = arr[k];
        }

        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; ++k)
        {
            if (i > mid)                    a[k] = aux[j++];
            else if (j > hi)                a[k] = aux[i++];
            else if (less(aux[j], aux[i]))  a[k] = aux[j++];
            else                            a[k] = aux[i++];
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
        aux = new Comparable[a.length];
        for (int i = 0; i < arr.length; i++) {
            aux[i] = arr[i];
        }

        sort(arr, aux, 0, a.length-1);
    }
}

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdRandom;

public class Permutation {
    public static void main(String[] args) {
        
        if (args.length != 1)
            throw new IllegalArgumentException("New give a number params");

        String[] perm = new String[Integer.parseInt(args[0])];

        for (int i = 0; i < perm.length; i++) {
            if (StdIn.isEmpty())
                throw new IllegalArgumentException("New give a number params");
            perm[i] = StdIn.readString();
        }

        int i = 0;
        for (; i < perm.length; i++) {
            int r = StdRandom.uniform(i+1);
            String tmp = perm[i];
            perm[i] = perm[r];
            perm[r] = tmp;
        }

        for (; !StdIn.isEmpty(); i++) {
            int r = StdRandom.uniform(i+1);
            String v = StdIn.readString();
            if (r < perm.length) perm[r] = v;
        }

        for (int j = 0; j < perm.length; j++) {
            StdOut.println(perm[j]);
        }
    }
}

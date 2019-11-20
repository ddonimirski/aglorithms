import java.util.Iterator;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;

public class Permutation {
    public static void main(String[] args) {
        
        if (args.length != 1)
            throw new IllegalArgumentException("New give a number params");
        int k = Integer.parseInt(args[0]);
        if (k < 1)
            return;

        RandomizedQueue<String> queue = new RandomizedQueue<>();

        while (!StdIn.isEmpty()) {
            String v = StdIn.readString();
            if (k == queue.size())
                queue.dequeue();
            queue.enqueue(v);
        }

        Iterator<String> iter = queue.iterator();
        while (iter.hasNext())
            StdOut.println(iter.next());

    }
}

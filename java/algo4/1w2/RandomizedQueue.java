import java.util.Iterator;
import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class RandomizedQueue<Item> implements Iterable<Item> {

    private Item[] array;
    private int size;

    // construct an empty randomized queue
    public RandomizedQueue() {
        this.array = createArray(0);
    }

    // is the randomized queue empty?
    public boolean isEmpty() { return this.size == 0; }

    // return the number of items on the randomized queue
    public int size() { return this.size; }

    // add the item
    public void enqueue(Item item) {
        if (item == null)
            throw new IllegalArgumentException("enqueue got null value");

        if (this.array.length == this.size)
        {
            Item[] tmp = createArray(this.array.length*2 + 1);
            for (int i = 0; i < this.size; i++) {
                tmp[i] = this.array[i];
            }
            this.array = tmp;
        }

        this.array[this.size++] = item;
    }

    // remove and return a random item
    public Item dequeue() {
        if (isEmpty())
            throw new NoSuchElementException("RandomizedQueue is empty");
        swap(StdRandom.uniform(this.size), --this.size);

        Item ret = this.array[this.size];

        if (this.array.length/3 == this.size)
        {
            Item[] tmp = createArray(this.array.length/2 + 1);
            for (int i = 0; i < this.size; i++) {
                tmp[i] = this.array[i];
            }
            this.array = tmp;
        }

        return ret;
    }

    private void swap(int i, int j) {
        Item tmp = this.array[i];
        this.array[i] = this.array[j];
        this.array[j] = tmp;
    }

    // return a random item (but do not remove it)
    public Item sample() {
        if (isEmpty())
            throw new NoSuchElementException("RandomizedQueue is empty");
        return this.array[StdRandom.uniform(this.size)];
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator();
    }

    // unit testing (required)
    public static void main(String[] args) {
        RandomizedQueue<Integer> arr = new RandomizedQueue<Integer>();

        arr.enqueue(1);
        arr.enqueue(2);
        arr.enqueue(3);
        arr.enqueue(4);
        while (!arr.isEmpty())
            StdOut.println(arr.dequeue());

        arr.enqueue(1);
        arr.enqueue(2);
        arr.enqueue(3);

        Iterator<Integer> iter = arr.iterator();
        while (iter.hasNext()) {
            StdOut.println(iter.next());
        }
    }

    private Item[] createArray(int newSize) {
        return (Item[]) new Object[newSize];
    }

    private class RandomizedQueueIterator implements Iterator<Item> {

        int current;
        int[] idArray;

        public RandomizedQueueIterator() {
            this.idArray = new int[size];
            for (int i = 0; i < size; i++)
                this.idArray[i] = i;
            StdRandom.shuffle(this.idArray);
            this.current = 0;
        }

        public Item next() {
            if (!hasNext())
                throw new NoSuchElementException("there is no next");
            return array[this.idArray[this.current++]];
        }

        public boolean hasNext() {
            return this.current < size;
        }
    }
}

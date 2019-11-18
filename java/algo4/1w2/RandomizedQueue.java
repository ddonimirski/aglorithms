import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.StdOut;

public class RandomizedQueue<Item> implements Iterable<Item> {

    ArrayMgr<Item> arr;

    // construct an empty randomized queue
    public RandomizedQueue() {
    }

    // is the randomized queue empty?
    public boolean isEmpty() {
        return true;
    }

    // return the number of items on the randomized queue
    public int size() { return 0; }

    // add the item
    public void enqueue(Item item) {

    }

    // remove and return a random item
    public Item dequeue() {
        return null;
    }

    // return a random item (but do not remove it)
    public Item sample() {
        return null; //TODO:
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return null; //TODO:
    }

    // unit testing (required)
    public static void main(String[] args) {
        RandomizedQueue<Integer> arr;

        int[] init_arr = { 1, 2 };
        int size = 2;
        
        
    }

}

class ArrayMgr <Item> {
    private Object[] array;
    private int size;
    private int capacity;

    public ArrayMgr() {
        this.array = null;
        this.size = 0;
        this.capacity = 0;
    }

    public int size() {
        return this.size;
    }

    public void add(Item item) {
        if (this.capacity == this.size) {
            this.capacity = 2 * this.capacity;
            this.array = new Object[this.capacity];
        }
    }

    public Item get(int i) {
        return (Item) array[i];
    }

}

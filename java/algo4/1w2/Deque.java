import java.util.Iterator;
import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.StdOut;
//import edu.princeton.cs.algs4.StdRandom;

public class Deque<Item> implements Iterable<Item> {

    private Node<Item> head, tail;
    private int size;

    protected Node<Item> getHead() { return this.head; }
    protected Node<Item> getTail() { return this.tail; }


    // construct an empty deque
    public Deque() {
        this.head = null;
        this.tail = null;
        this.size = 0;

    }

    // is the deque empty?
    public boolean isEmpty() { return this.size == 0; }

    // return the number of items on the deque
    public int size() { return this.size; }

    // add the item to the front
    public void addFirst(Item item) {
        if (item == null)
            throw new IllegalArgumentException("addFirst got null value");
        Node<Item> tmp = new Node<>(item);
        if (isEmpty()) {
            this.head = tmp;
            this.tail = tmp;
        } else {
            tmp.next = head;
            head.prev = tmp;
            head = tmp;
        }
        this.size++;
    }

    // add the item to the back
    public void addLast(Item item) {
        if (item == null)
            throw new IllegalArgumentException("addLast got null value");
        Node<Item> tmp = new Node<>(item);
        if (isEmpty()) {
            this.head = tmp;
            this.tail = tmp;
        } else {
            tmp.prev = tail;
            tail.next = tmp;
            tail = tmp;
        }
        this.size++;
    }

    // remove and return the item from the front
    public Item removeFirst() {
        if (isEmpty())
            throw new NoSuchElementException("Dqeue is empty");
        Item ret = head.data;
        if (size() == 1) {
            this.head = null;
            this.tail = null;
        } else {
            this.head = this.head.next;
            this.head.prev = null;
        }
        this.size--;
        return ret;
    }

    // remove and return the item from the back
    public Item removeLast() {
        if (isEmpty())
            throw new NoSuchElementException("Dqeue is empty");
        Item ret = tail.data;
        if (size() == 1) {
            this.head = null;
            this.tail = null;
        } else {
            this.tail = this.tail.prev;
            this.tail.next = null;
        }
        this.size--;
        return ret;
    }

    // return an iterator over item in order from front to back
    public Iterator<Item> iterator() {
        return new DequeIterator<Item>(this);
    }


    public static void main(String[] args) {
        Deque<Integer> deque = new Deque<>();
        assert deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 0 : "size() should be 0";

        try {
            deque.addFirst(null);
        } catch(IllegalArgumentException exp) {
        }

        try {
            deque.addLast(null);
        } catch(IllegalArgumentException exp) {
        }

        try {
          Integer item = deque.removeFirst();
          assert false: "Exception should be thrown";
        } catch(NoSuchElementException exp) {
        }

        try {
          Integer item = deque.removeLast();
          assert false: "Exception should be thrown";
        } catch(NoSuchElementException exp) {
        }


        deque.addFirst(1);
        assert !deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 1 : "size() should be 1";

        deque.addFirst(2);
        assert !deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 2 : "size() should be 2";

        {
            Integer item = deque.removeFirst();
            assert item == 1 : "should be 1";
            assert !deque.isEmpty() : "isEmpty() Failed";
            assert deque.size() == 1 : "size() should be 1";
        }

        {
            Integer item = deque.removeLast();
            assert item == 2 : "should be 2";
            assert deque.isEmpty() : "isEmpty() Failed";
            assert deque.size() == 0 : "size() should be 1";
        }

        try {
          Integer item = deque.removeFirst();
          assert false: "Exception should be thrown";
        } catch(NoSuchElementException exp) {
        }

        try {
          Integer item = deque.removeLast();
          assert false: "Exception should be thrown";
        } catch(NoSuchElementException exp) {
        }

        deque.addFirst(1);
        assert !deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 1 : "size() should be 1";

        deque.addFirst(2);
        assert !deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 2 : "size() should be 2";

        {
            Integer item = deque.removeLast();
            assert item == 2 : "should be 2";
            assert deque.isEmpty() : "isEmpty() Failed";
            assert deque.size() == 0 : "size() should be 1";
        }

        {
            Integer item = deque.removeFirst();
            assert item == 1 : "should be 1";
            assert !deque.isEmpty() : "isEmpty() Failed";
            assert deque.size() == 1 : "size() should be 1";
        }

        try {
          Integer item = deque.removeFirst();
          assert false: "Exception should be thrown";
        } catch(NoSuchElementException exp) {
        }

        try {
          Integer item = deque.removeLast();
          assert false: "Exception should be thrown";
        } catch(NoSuchElementException exp) {
        }

        deque.addLast(3);
        assert !deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 2 : "size() should be 2";

        deque.addFirst(2);
        assert !deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 3 : "size() should be 1";

        deque.addLast(4);
        assert !deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 4 : "size() should be 2";

        deque.addFirst(1);
        assert !deque.isEmpty() : "isEmpty() Failed";
        assert deque.size() == 1 : "size() should be 1";


        Iterator<Integer> iter = deque.iterator();
        int i = 1;

        while(iter.hasNext()) {
            Integer item = iter.next();
            StdOut.println(item);
            assert i == item: "iter failed";
            i++;
        }

        i = 1;

        while(!deque.isEmpty()) {
            Integer item = deque.removeFirst();
            StdOut.println(item);
            assert i == item: "iter failed";
        }

        StdOut.println("Deque OK");
    }
}

class DequeIterator<Item> implements Iterator<Item> {

    Node<Item> current;

    public DequeIterator(Deque<Item> deque) {
        if (deque == null)
            throw new IllegalArgumentException("DequeIterator has got null value");
        current = deque.getHead();
    }

    public Item next() {
        if (current == null)
            throw new NoSuchElementException("Dqeue is empty");
        Item ret = current.getData();
        current = current.getNext();
        return ret;
    }

    public boolean hasNext() {
        return current != null;
    }
}

class Node<Item> {
    Item data;
    public Node<Item> next, prev;

    public Node(Item data, Node<Item> next, Node<Item> prev) {
        this.data = data;
        this.next = next;
        this.prev = prev;
    }

    public Node(Item data) {
        this.data = data;
        this.next = null;
        this.prev = null;
    }

    Item getData() { return this.data; }
    Node<Item> getNext() { return this.next; }
    Node<Item> getPrev() { return this.prev; }
}

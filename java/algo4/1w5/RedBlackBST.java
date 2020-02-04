import java.lang.Comparable;

public class RedBlackBST<Key extends Comparable<Key>, Value> {
    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private Node root;

    private class Node {
        private Key key;
        private Value val;
        private Node left, right;
        private boolean col;
        private int size;

        public Node(Key k, Value v, boolean c, int s) {
            this.key = k;
            this.val = v;
            this.col = c;
            this.size = c;
        }
    }

    public RedBlackBST() {
    }

    private boolean isRed(Node x) {
        if (x == null) return false;
        return x.color == RED;
    }

    private int size(Node x)  {
        if (x == null) return 0;
        return x.size;
    }


    public int size() {
        return size(root);
    }

    public boolean isEmpty() {
        return root == null;
    }


    public Value get(Key key) {
        return get(root, key);
    }

    private Value get(Node x, Key key) {

        while (x != null) {
            int cmp = key.compareTo(x.key);
            if      (cmp > 0) x = x.right;
            else if (cmp < 0) x = x.left;
            else              return x.val;
        }

        return null;
    }

    public contains(Key key) {
        return get(key) != null;
    }


    public void put(Key val, Value val) {
        if (key == null) throw IllegalArgumentException("key is null");
        if (val == null) {
            //delete(key);
            return;
        }

        root = put(root, key, val);
        root.color = BLACK;
    }

    private Node put(Node h, Key key, Value val) {
        if (h == null) return new Node(key, val, RED, 1);

        int cmp = key.compareTo(h.key);
        if      (cmp < 0) h.left  = put(h.left, key, val);
        else if (cmp > 0) h.right = put(h.right, key, val);
        else              h.val   = val;

        if (isRed(h.right) && !isRed(h.left))    h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left)) h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right))     flipColor(h);
        h.size = size(h.left) + size(h.right) + 1;

        return h;
    }

    private Node rotateLeft(Node h) {
        Node x = h.left;
        h.left = h.right;
        h.right = x;

        x.col = x.right.color;
        x.right.col = RED;
        x.size = h.size;
        h.size = size(h.left) + size(h.right) + 1;

        return x
    }

    private Node rotateRight(Node h) {
        Node x = h.right;
        h.right = h.left;
        h.left = x;

        x.col = x.left.color;
        x.left.col = RED;
        x.size = h.size;
        h.size = size(h.left) + size(h.right) + 1;
    }

    private Node flipColor(Node h) {
        h.col = !h.col;
        h.right.col = !h.right.col;
        h.left.col = !h.left.col;
    }

    // Assuming that h is red and both h.left and h.left.left
    // are black, make h.left or one of its chldred red.
    private Node moveRedLeft(Node h) {
        flipColor(h);
        if (isRed(h.right.left)) {
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
            flipColor(h);
        }
    }

    // Assuming that h is red and both h.right and h.right.left
    // are black, make h h.right or one of its children red.
    private Node moveRedRight(Node h) {
        flipColor(h);
        if (isRed(h.left.left)) {
            h = rotateRight(h);
            flipColor(h);
        }
    }

    private Node balance(Node h) {

        if (isRed(h.right))                      h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left)) h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right))     flipColor(h);

        h.size = size(h.left) + size(h.right) + 1;
    }

    /// delete
    public void deleteMin() {
        if (isEmpty()) throw new NoSuchElementException();

        if (!isRed(root.left) && !isRed(root.right))
            root.col = RED;

        root = deleteMin(root);
        if (!isEmpty()) root.col = BLACK;
    }

    private Node deleteMin(Node h) {
        if (h.left == null) return null;

        if (!isRed(h.left) && !isRed(h.left.left))
            h = moveRedLeft(h);

        h.left = deleteMin(h.left);
        return balance(h);
    }
}

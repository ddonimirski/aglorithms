import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import java.util.LinkedList;
import java.util.List;

public class Board {

    private final int[][] tiles;
    private int row;
    private int col;

    // create a board from an n-by-n array of tiles,
    // where tiles[row][col] = tile at (row, col)
    public Board(int[][] tiles) {

        if (tiles == null || tiles.length < 2 || tiles[0].length < 2) {
            throw new IllegalArgumentException();
        }

        this.tiles = clone(tiles);
        final int N = this.tiles.length;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (0 == this.tiles[i][j]) {
                    row = i;
                    col = j;
                }
            }
        }
    }
                                           
    // string representation of this board
    public String toString() {
        final int N = this.dimension();
        StringBuilder ret = new StringBuilder(String.format("%d\n", N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ret.append(String.format(" %d", this.tiles[i][j]));
            }
            ret.append("\n");
        }
        return ret.toString();
    }

    // board dimension n
    public int dimension() {
        return this.tiles.length;
    }

    // number of tiles out of place
    public int hamming() {
        final int N = this.dimension();
        int ret = 0;
        int v = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j, ++v) {
                if (v != this.tiles[i][j] && this.tiles[i][j] != 0) {
                    // if (this.row == N-1 && this.col == N-1 && this.tiles[i][j] == 0) {
                    //     continue;
                    // }
                    ret++;
                }
            }
        }
        return ret;
    }

    // sum of Manhattan distances between tiles and goal
    public int manhattan() {
        final int N = dimension();
        if (0 == N) return 0;
        int v = 1;
        int m = 0;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c, ++v) {
                if (tiles[r][c] == 0 || tiles[r][c] == v) continue;
                final int rv = (tiles[r][c]-1) / N;
                final int cv = (tiles[r][c]-1) % N;
                final int vv = Math.abs(rv - r) + Math.abs(cv - c);
                // StdOut.print("\nAdd:");
                // StdOut.print("[");
                // StdOut.print(r);
                // StdOut.print("]");
                // StdOut.print("[");
                // StdOut.print(c);
                // StdOut.print("]");
                // StdOut.print(tiles[r][c]);
                // StdOut.print(" != ");
                // StdOut.print(v);
                // StdOut.print(", ");
                // StdOut.print("[");
                // StdOut.print(rv);
                // StdOut.print("]");
                // StdOut.print("[");
                // StdOut.print(cv);
                // StdOut.print("]");
                // StdOut.println(vv);
                m += vv;
            }
        }
        return m;
    }

    // is this board the goal board?
    public boolean isGoal() {
        int v = 1;
        final int N = this.dimension();
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j, ++v) {
                if (v != this.tiles[i][j]) {
                    return i == N-1 && j == N-1;
                }
            }
        }
        return true;
    }

    // does this board equal y?
    public boolean equals(Object y) {
        if (null == y || this.getClass() != y.getClass())
            return false;
        if (this == y) return true;
        final int N = this.dimension();
        Board b = (Board) y;
        if (this.col != b.col || this.row != b.row)
            return false;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (b.tiles[i][j] != this.tiles[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    private static int[][] clone(int[][] in) {
        // if (in == null) return in;

        int[][] arr = new int[in.length][];
        for (int i = 0; i < in.length; ++i) {
            arr[i] = in[i].clone();
        }
        return arr;
    }

    private void swap(int[][] t, int r1, int c1, int r2, int c2) {
        int v = t[r1][c1];
        t[r1][c1] = t[r2][c2];
        t[r2][c2] = v;

        // StdOut.print("swap");
        // StdOut.println(this);
    }

    // all neighboring boards
    public Iterable<Board> neighbors() {

        List<Board> ret = new LinkedList<Board>();
        final int N = this.dimension();

        if (this.col > 0) {
            int[][] t = clone(this.tiles);
            swap(t, this.row, this.col, this.row, this.col-1);
            ret.add(new Board(t));
        }

        if (this.row > 0) {
            int[][] t = clone(this.tiles);
            swap(t, this.row, this.col, this.row-1, this.col);
            ret.add(new Board(t));
        }

        if (this.col < N-1) {
            int[][] t = clone(this.tiles);
            swap(t, this.row, this.col, this.row, this.col+1);
            ret.add(new Board(t));
        }

        if (this.row < N-1) {
            int[][] t = clone(this.tiles);
            swap(t, this.row, this.col, this.row+1, this.col);
            ret.add(new Board(t));
        }

        return ret;
    }

    // a board that is obtained by exchanging any pair of tiles
    public Board twin() {
        int [][] tt = clone(this.tiles);
        if (tiles[0][0] != 0 && tiles[0][1] != 0) {
            swap(tt, 0, 0, 0, 1);
        } else {
            swap(tt, 1, 0, 1, 1);
        }

        return new Board(tt);
    }

    // unit testing (not graded)
    public static void main(String[] args) {

        // create initial board from file
        In in = new In(args[0]);
        int n = in.readInt();
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                tiles[i][j] = in.readInt();
        Board board = new Board(tiles);

        StdOut.println("board:");
        StdOut.println(board);
        StdOut.print("dimention: ");
        StdOut.println(board.dimension());
        StdOut.print("isGoal: ");
        StdOut.println(board.isGoal());
        StdOut.print("equals: ");
        StdOut.println(board.equals(new Board(tiles)));
        StdOut.print("manhattan: ");
        StdOut.println(board.manhattan());
        StdOut.print("hamming: ");
        StdOut.println(board.hamming());

        for (Board b: board.neighbors()) {
            StdOut.println("--------------------");
            StdOut.println(b);
            StdOut.println(b.dimension());
            StdOut.println(b.isGoal());
            StdOut.println(b.manhattan());
            StdOut.println(b.hamming());
        }
        StdOut.println("--------------------");
        StdOut.println(board.twin());
    }
}

import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.In;
import java.lang.String;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.List;

public class Board {

    private final int[][] tiles;
    private int row;
    private int col;

    // create a board from an n-by-n array of tiles,
    // where tiles[row][col] = tile at (row, col)
    public Board(int[][] tiles) {
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
        String ret = String.format("%d\n", N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ret +=  String.format(" %d", this.tiles[i][j]);
            }
            ret = ret + "\n";
        }
        return ret;
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
            for (int j = 0; j < N; ++j) {
                if (v++ != this.tiles[i][j]) {
                    if (this.row == N-1 && this.col == N-1 && this.tiles[i][j] == 0) {
                        continue;
                    }
                    ret++;
                }
            }
        }
        return ret;
    }

    // sum of Manhattan distances between tiles and goal
    public int manhattan() {
        final int N = this.dimension();
        if (0 == N) return 0;
        return 2*(N - 1) - (row + col);
    }

    // is this board the goal board?
    public boolean isGoal() {
        int c = 1;
        final int N = this.dimension();
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (c++ != this.tiles[i][j]) {
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
        Board b = (Board)y;
        if (this.col != b.col || this.row != b.row)
            return false;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (b.tiles[i][j] != this.tiles[i][j]) {
                    StdOut.print(this.tiles[i][j]);
                    StdOut.print(' ');
                    StdOut.println(b.tiles[i][j]);
                    return false;
                }
            }
        }
        return true;
    }

    private static int[][] clone(int[][] in) {
        if (in == null) return new int[0][0];

        int[][] arr = new int[in.length][];
        for (int i = 0; i < in.length; ++i) {
            arr[i] = in[i].clone();
        }
        return arr;
    }

    private void swap(int[][] tiles, int r1, int c1, int r2, int c2) {
        int v = tiles[r1][c1];
        tiles[r1][c1] = tiles[r2][c2];
        tiles[r2][c2] = v;

        //StdOut.print("swap");
        //StdOut.println(this);
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
        final int N = this.dimension();
        int [][] tt = clone(this.tiles);

        int r = StdRandom.uniform(N);
        int c = StdRandom.uniform(N);

        if (r > 0) {
            swap(tt, r, c, r-1, c);
        } else if (c > 0) {
            swap(tt, r, c, r, c-1);
        } else if (r < N-1) {
            swap(tt, r, c, r+1, c);
        } else if (c < N-1) {
            swap(tt, r, c, r, c+1);
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

        StdOut.println(board);
        StdOut.println(board.dimension());
        StdOut.println(board.isGoal());
        StdOut.println(board.equals(new Board(tiles)));
        StdOut.println(board.manhattan());
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

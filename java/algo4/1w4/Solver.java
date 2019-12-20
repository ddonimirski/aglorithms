import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.MinPQ;
import java.util.Deque;
import java.util.LinkedList;

public class Solver {

    private boolean isSolvable;
    private MinPQ<Node> queue;
    private Node solutionNode;

    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial) {

        solutionNode = null;
        queue = new MinPQ<>();
        queue.insert(new Node(initial, 0, null));

        while (queue.size() > 0) {

            Node currNode = queue.delMin();
            Board currBoard = currNode.getBoard();

            //StdOut.print("get min");
            //StdOut.print(currBoard);

            if (currBoard.isGoal()) {
                this.isSolvable = true;
                this.solutionNode = currNode;
                break;
            }

            if (currBoard.twin().isGoal()) {
                this.isSolvable = false;
                this.solutionNode = null;
                break;
            }

            int moves = currNode.moves();
            Board prevBoard = moves > 0 ? currNode.prev().getBoard() : null;

            for (Board next : currBoard.neighbors()) {
                if (prevBoard != null && next.equals(prevBoard)) {
                    continue;
                }
                //StdOut.println("add new");
                queue.insert(new Node(next, moves+1, currNode));
            }
        }
    }

    // is the initial board solvable? (see below)
    public boolean isSolvable() {
        return isSolvable;
    }

    // min number of moves to solve initial board
    public int moves() {
        return isSolvable() ? solutionNode.moves(): -1;
    }

    // sequence of boards in a shortest solution
    public Iterable<Board> solution() {
        if (!isSolvable) { return null; }

        Deque<Board> solution = new LinkedList<>();
        Node node = solutionNode;
        while (node != null) {
            solution.addFirst(node.getBoard());
            node = node.prev();
        }

        return solution;
    }

    // test client (see below) 
    public static void main(String[] args) {
        // create initial board from file
        In in = new In(args[0]);
        int n = in.readInt();
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                tiles[i][j] = in.readInt();
        Board initial = new Board(tiles);

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }

    private class Node implements Comparable<Node> {
        private final Node prev;
        private final Board board;
        private final int moves;

        Node(Board b, int m, Node p) {
            this.board = b;
            this.moves = m;
            this.prev = p;
        }

        @Override
        public int compareTo(Node that) {
            return this.priority() - that.priority();
        }

        public int priority() {
            return board.manhattan() + this.moves;
        }

        public Board getBoard() { return this.board; }
        public int moves() { return this.moves; }
        public Node prev() { return this.prev; }
    }
}

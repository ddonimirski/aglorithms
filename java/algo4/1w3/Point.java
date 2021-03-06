import java.util.Comparator;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdDraw;

public class Point implements Comparable<Point> {
    private final int x;
    private final int y;


    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    // draws this point
    public void draw() { StdDraw.point(x, y); }

    // draws the line segment from this point to that point
    public void drawTo(Point that) { StdDraw.line(this.x, this.y, that.x, that.y); }

    // string reprezentation
    public String toString() { return "(" + x + ", " + y + ")"; }

    // Compares two points by y-coordinate, breaking ties by x-coordinate.
    // Formally, the invoking point (x0, y0) is less than the argument point
    // (x1, y1) if and only if either y0 < y1 or if y0 = y1 and x0 < x1.
    // @param  that the other point
    // @return the value <tt>0</tt> if this point is equal to the argument
    //         point (x0 = x1 and y0 = y1);
    //         a negative integer if this point is less than the argument
    //         point; and a positive integer if this point is greater than the
    //         argument point
    public int compareTo(Point that) {
        if (that == null) throw new NullPointerException();
        if (this.x == that.x && this.y == that.y) return 0;
        if (this.y < that.y || (this.y == that.y && this.x < that.x)) return -1;
        return 1;
    }

    // Returns the slope between this point and the specified point.
    // Formally, if the two points are (x0, y0) and (x1, y1), then the slope
    // is (y1 - y0) / (x1 - x0). For completeness, the slope is defined to be
    // +0.0 if the line segment connecting the two points is horizontal;
    // Double.POSITIVE_INFINITY if the line segment is vertical;
    // and Double.NEGATIVE_INFINITY if (x0, y0) and (x1, y1) are equal.
    // @param  that the other point
    // @return the slope between this point and the specified point
    public double slopeTo(Point that) {
        if (that.x == this.x && that.y == this.y) {
            return Double.NEGATIVE_INFINITY;
        }

        if (that.y == this.y) {
            return +0.0;
        }

        if (that.x == this.x) {
            return Double.POSITIVE_INFINITY;
        }

        if (this.x < that.x) return ((double) that.y - this.y) / ((double) that.x - this.x);
        return ((double) this.y - that.y) / ((double) this.x - that.x);
    }

    private static class Less implements Comparator<Point> {
        public int compare(Point x1, Point x2) { return (x1.compareTo(x2) - 1);  }
    }


    // compare two point by  slopes they make with this point
    public Comparator<Point> slopeOrder() {
        return (Point p, Point q) -> {
            return Double.compare(slopeTo(p), slopeTo(q));
        };
    }


    // unit tests
    public static void main(String[] args) {
        Point x1 = new Point(1, 1);
        Point x2 = new Point(2, 2);

        StdOut.println(x1.compareTo(x2) < 0);
        StdOut.println(x1.slopeTo(x2));

        x1 = new Point(10000, 0);
        x2 = new Point(3000, 7000);

        StdOut.println(x1.compareTo(x2) < 0);
        StdOut.println(x1.slopeTo(x2));

        Point[] arr = new Point[3];
        arr[0] = new Point(10000, 0);
        arr[1] = new Point(0, 10000);
        arr[2] = new Point(3000, 7000);

        StdOut.println(arr[0].compareTo(arr[2]));
        StdOut.println(arr[0].compareTo(arr[1]));

    }
}

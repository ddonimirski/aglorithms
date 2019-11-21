import java.util.Comparator;
import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
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
    //
    // @param  that the other point
    // @return the value <tt>0</tt> if this point is equal to the argument
    //         point (x0 = x1 and y0 = y1);
    //         a negative integer if this point is less than the argument
    //         point; and a positive integer if this point is greater than the
    //         argument point
    public int compareTo(Point that) {
        if (this.x == that.x && this.y == that.y) return 0;
        if (this.y < that.y || (this.y == this.y && this.x < that.x)) return -1;
        return 1;
    }

    // Returns the slope between this point and the specified point.
    // Formally, if the two points are (x0, y0) and (x1, y1), then the slope
    // is (y1 - y0) / (x1 - x0). For completeness, the slope is defined to be
    // +0.0 if the line segment connecting the two points is horizontal;
    // Double.POSITIVE_INFINITY if the line segment is vertical;
    // and Double.NEGATIVE_INFINITY if (x0, y0) and (x1, y1) are equal.
    //
    // @param  that the other point
    // @return the slope between this point and the specified point
    public double slopeTo(Point that) {
        if (that.x == this.x && that.y == this.y) return Double.NEGATIVE_INFINITY;
        if (that.y == this.y) return +0.0;
        if (that.x == this.x) return Double.POSITIVE_INFINITY;
        if (this.x < that.x) return (that.y - this.y) / (that.x - this.x);
        return (this.y - that.y) / (this.x - that.x);
    }

    private static class Less implements Comparator<Point> {
        public int compare (Point x1, Point x2) { return x1.compareTo(x2) < 0;  }
    }
    private static class Qual implements Comparator<Point> {
        public int compare (Point x1, Point x2) { return x2.compareTo(x1) == 0; }
    }
    private static class Greater implements Comparator<Point> {
        public int compare (Point x1, Point x2) { return x1.compareTo(x2) > 0; }
    }
    private static class SlopeOrder implements Comparator<Point> {
        public int compare (Point x1, Point x2) {
            return x1.slopeTo(zero) < x2.slopeTo(zero);
        }
    }

    private final Point zero = new Point(0,0);
    private final SlopeOrder fslopeOrder = new SlopeOder();

    // compare two point by  slopes they make with this point
    public Comparator<Point> slopeOrder() {
        return this.fslopeOrder;
    }

    // unit tests
    public static void main(String[] args) {
        Point x1 = new Point(1,1);
        Point x2 = new Point(2,2);

        StdOut.println(x1.compareTo(x2)<0);
        StdOut.println(x1.slopeTo(x2));
    }
}

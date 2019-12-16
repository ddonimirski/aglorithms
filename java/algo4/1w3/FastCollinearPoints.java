import java.util.Arrays;
import java.util.ArrayList;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdDraw;

public class FastCollinearPoints {

    private final LineSegment[] lineSegments;

    public FastCollinearPoints(Point[] points) {     // finds all line segments containing 4 or more points
        if (points == null)
            throw new IllegalArgumentException("FastCollinearPoints has got null value");
        for (int i = 0; i < points.length; ++i) {
            if (points[i] == null)
                throw new IllegalArgumentException("FastCollinearPoints has got null value");
        }

        ArrayList<LineSegment> arr = new ArrayList<LineSegment>();

        int c = 0;
        for (int i = 0; i < points.length-1; ++i) {
            Arrays.sort(points);
            Point left = points[i];
            Arrays.sort(points, left.slopeOrder());
            Point right = points[i+1];
            if (less(right, left)) {
                Point t = left;
                left = right;
                right = t;
            }
            final double slope = left.slopeTo(right);
            c = 2;
            for (int j = i + 2; j < points.length; ++j) {
                Point tmp = points[j];
                if (slope == left.slopeTo(tmp)) {
                    ++c;
                    if (less(tmp, left)) {
                        left = tmp;
                    }
                    if (less(right, tmp)) {
                        right = tmp;
                    }
                }
            }
            if (c >= 4) {
                arr.add(new LineSegment(left, right));
            }
        }


        this.lineSegments = arr.toArray(new LineSegment[arr.size()]);
    }

    public           int numberOfSegments() {       // the number of line segments
        return this.lineSegments.length;
    }

    public LineSegment[] segments() {               // the line segments 
        return this.lineSegments.clone();
    }

    public static void main(String[] args) {

        // read the n points from a file
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }

        // draw the points
        StdDraw.enableDoubleBuffering();
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();

        // print and draw the line segments
        FastCollinearPoints collinear = new FastCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }

    private boolean less(Point p, Point r) {
        return p.compareTo(r) < 0;
    }

}

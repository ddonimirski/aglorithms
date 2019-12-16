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


        Point[] pPoints = points.clone();
        Arrays.sort(pPoints);
        check(pPoints);
        Point[] sPoints = points.clone();
        ArrayList<LineSegment> ls = new ArrayList<LineSegment>();

        for (int i = 0; i < pPoints.length; ++i) {
            Point left = pPoints[i];
            Arrays.sort(sPoints, left.slopeOrder());

            int j = 1;
            while (j < sPoints.length) {

                final double SLOPE = left.slopeTo(sPoints[j]);
                ArrayList<Point> arr = new ArrayList<Point>();

                do {
                    arr.add(sPoints[j++]);
                } while (j < sPoints.length && 0 == Double.compare(left.slopeTo(sPoints[j]), SLOPE));

                if (arr.size() >= 3) {
                    Point[] pp = arr.toArray(new Point[arr.size()]);
                    Arrays.sort(pp);
                    if (less(left, pp[0])) {
                        ls.add(new LineSegment(left, pp[arr.size()-1]));
                    }
                }
            }
        }

        this.lineSegments = ls.toArray(new LineSegment[ls.size()]);
    }

    private void check(Point[] points) {
        // must be sorted
        for (int i = 0; i < points.length-1; ++i) {
            if (points[i].compareTo(points[i+1]) == 0) {
                throw new IllegalArgumentException("Found duplicates");
            }
        }
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

import java.util.Arrays;
import java.util.ArrayList;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdDraw;

public class BruteCollinearPoints {

    private final LineSegment[] lineSegments;

    public BruteCollinearPoints(Point[] ppoints) {
        if (ppoints == null)
            throw new IllegalArgumentException("BruteCollinearPoints has got null value");

        for (int i = 0; i < ppoints.length; ++i) {
            if (ppoints[i] == null)
                throw new IllegalArgumentException("Points should not have nulls points");
        }

        Point[] points = ppoints.clone();
        Arrays.sort(points);
        check(points);
        ArrayList<LineSegment> arr = new ArrayList<LineSegment>();

        for (int i = 0; i < points.length-3; ++i) {
            Point left = points[i];

            for (int j = i+1; j < points.length-2; ++j) {

                Point tmp = points[j];
                double slope = left.slopeTo(tmp);
                for (int k = j+1; k < points.length-1; ++k) {
                    tmp = points[k];
                    double slopeTmp = left.slopeTo(tmp);
                    if (Double.compare(slope, slopeTmp) != 0) continue;

                    for (int ll = k+1; ll < points.length; ++ll) {
                        tmp = points[ll];
                        slopeTmp = left.slopeTo(tmp);

                        if (Double.compare(slope, slopeTmp) != 0) continue;

                        arr.add(new LineSegment(left, tmp));
                    }
                }
            }
        }

        this.lineSegments = arr.toArray(new LineSegment[arr.size()]);
    }

    private void check(Point[] points) {
        // must be sorted
        for (int i = 0; i < points.length-1; ++i) {
            if (points[i].compareTo(points[i+1]) == 0) {
                throw new IllegalArgumentException("Found duplicates");
            }
        }
    }

    public int numberOfSegments() {       // the number of line segments
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
        BruteCollinearPoints collinear = new BruteCollinearPoints(points);
        LineSegment[] seg  = collinear.segments();
        if (seg == null)
            return;
        for (LineSegment segment : seg) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }
}

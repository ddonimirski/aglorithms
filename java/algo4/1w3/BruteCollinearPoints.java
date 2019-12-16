import java.util.ArrayList;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdDraw;

public class BruteCollinearPoints {

    private final LineSegment[] lineSegments;

    public BruteCollinearPoints(Point[] points) {
        if (points == null)
            throw new IllegalArgumentException("BruteCollinearPoints has got null value");

        for (int i = 0; i < points.length; ++i) {
            if (points[i] == null)
                throw new IllegalArgumentException("Points should not have nulls points");
        }

        ArrayList<LineSegment> arr = new ArrayList<LineSegment>();

        for (int i = 0; i < points.length-3; ++i) {
            Point left = points[i];

            for (int j = i+1; j < points.length-2; ++j) {
                Point right = points[j];
                if (less(right, left)) {
                    Point t = left;
                    left = right;
                    right = t;
                }

                double slope = left.slopeTo(right);
                for (int k = j+1; k < points.length-1; ++k) {
                    Point tmp = points[k];
                    double slopeTmp;
                    if (less(left, tmp))
                        slopeTmp = left.slopeTo(tmp);
                    else
                        slopeTmp = tmp.slopeTo(left);

                    if (slope != slopeTmp) continue;

                    if (less(tmp, left)) {
                        Point t = tmp;
                        tmp = left;
                        left = t;
                    }

                    if (less(right, tmp)) {
                        Point t = tmp;
                        tmp = right;
                        right = t;
                    }
                    int c = 3;
                    for (int ll = k+1; ll < points.length; ++ll) {
                        tmp = points[ll];

                        if (less(left, tmp))
                            slopeTmp = left.slopeTo(tmp);
                        else
                            slopeTmp = tmp.slopeTo(left);

                        if (slope != slopeTmp) continue;

                        if (less(tmp, left)) {
                            Point t = tmp;
                            tmp = left;
                            left = t;
                        }

                        if (less(right, tmp)) {
                            Point t = tmp;
                            tmp = right;
                            right = t;
                        }
                        c++;
                    }
                    if (c >= 4) {
                        arr.add(new LineSegment(left, right));
                    }
                }
            }
        }

        this.lineSegments = arr.toArray(new LineSegment[arr.size()]);
    }

    private boolean less(Point p1, Point p2) {
        return p1.compareTo(p2) < 0;
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

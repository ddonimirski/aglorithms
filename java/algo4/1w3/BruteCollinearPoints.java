import java.util.Arrays;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Enumeration;
import java.util.Collection;
import java.util.Arrays;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdDraw;

public class BruteCollinearPoints {

    private LineSegment[] lineSegments;

    private void print(Point[] points) {
        for (Point p: points) {
            StdOut.print(p);
            StdOut.print(' ');
        }
        StdOut.println();
    }

    private void swap(Point l, Point r) {
        Point t = l;
        l = r;
        r = t;
    }

    private boolean less(Point l, Point r) {
        return l.compareTo(r) < 0;
    }


    public BruteCollinearPoints(Point[] points) {   // finds all line segments containing 4 points
        if (points == null)
            throw new IllegalArgumentException("BruteCollinearPoints has got null value");

        for (int i = 0; i < points.length; ++i) {
            if (points[i] == null)
                throw new IllegalArgumentException("Points should not have nulls points");
        }

        print(points);
        ArrayList<LineSegment> arr_tmp = new ArrayList<LineSegment>();

        for (int i = 0; i < points.length-3; ++i) {
            Point left = points[i];
            for (int j = i+1; j < points.length-2; ++j) {
                Point right = points[j];
                if (less(right, left)) swap(left ,right);
                double slope = left.slopeTo(right);
                for (int k = j+1; k < points.length-1; ++k) {
                    Point tmp = points[k];
                    if (less(tmp, left)) swap(tmp, left);
                    double slope_tmp = left.slopeTo(tmp);
                    if (slope != slope_tmp) continue;
                    if (less(right, tmp)) swap(tmp, right);
                    for (int l = k+1; l < points.length; ++l) {
                        tmp = points[l];
                        if (less(tmp, left)) swap(tmp, left);
                        slope_tmp = left.slopeTo(tmp);
                        if (slope != slope_tmp) continue;
                        if (less(right, tmp)) swap(tmp, right);
                        arr_tmp.add(new LineSegment(left, right));
                    }
                }
            }
        }

        lineSegments = arr_tmp.toArray(new LineSegment[arr_tmp.size()]);
    }


    public int numberOfSegments() {       // the number of line segments
        return this.lineSegments.length;
    }

    public LineSegment[] segments() {               // the line segments 
        return this.lineSegments;
    }

    private void pr(Point[] arr) {
        for (int i = 0; i < arr.length; ++i) {
            StdOut.print(arr[i]);
        }
        StdOut.println();
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
//        StdDraw.enableDoubleBuffering();
//        StdDraw.setXscale(0, 32768);
//        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
//            p.draw();
        }
//        StdDraw.show();


        // print and draw the line segments
        BruteCollinearPoints collinear = new BruteCollinearPoints(points);

        LineSegment[] seg  = collinear.segments();
        if (seg == null)
            return;
        for (LineSegment segment : seg) {
            StdOut.println(segment);
//            segment.draw();
        }
//        StdDraw.show();
    }
}

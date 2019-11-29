import java.util.Arrays;
import java.util.ArrayList;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdDraw;

public class BruteCollinearPoints {

    private LineSegment[] lineSegments;

    public BruteCollinearPoints(Point[] points) {   // finds all line segments containing 4 points
        if (points == null)
            throw new IllegalArgumentException("BruteCollinearPoints has got null value");

        for (int i = 0; i < points.length; ++i) {
            if (points[i] == null)
                throw new IllegalArgumentException("Points should not have nulls points");
        }

        ArrayList<tmpLine> ls = new ArrayList<>();
        tmpLine tl = new tmpLine();
        Point t;
        for (int i = 0; i < points.length-3; ++i) {
            tl.p = points[i];
            for (int j = i+1; j < points.length-2; ++j) {
                double ij = points[i].slopeTo(points[j]);
                tl.e = points[j];
                if (less(tl.e, tl.p)) 
                    swap(tl.e, tl.p);
                for (int k = j+1; k< points.length-1; ++k) {
                    double ik = points[i].slopeTo(points[k]);
                    if (ij != ik) continue;
                    t = points[k];
                    if (less(t, tl.p)) swap(t, tl.p);
                    if (less(tl.e, t)) swap(tl.e, t);
                    int c = 0;
                    for (int l = k+1; l < points.length; ++l) {
                        double il = points[i].slopeTo(points[l]);
                        if (ij != il) continue;
                        c++;
                        t = points[l];
                        StdOut.print(t); StdOut.println("t");
                        if (less(t, tl.p)) swap(t, tl.p);
                        if (less(tl.e, t)) swap(tl.e, t);
                        for (tmpLine v: ls) {
                            if (tl.slope == v.slope) {
                                c++;
                                if (less(tl.p, v.p)) v.p = tl.p;
                                if (less(v.e, tl.e)) v.e = tl.e;
                            }
                        }
                        pr(ls);
                    }
                    StdOut.println(c);
                    if (c == 1) ls.add(tl);
                }
            }
        }

                        pr(ls);
        this.lineSegments = new LineSegment[ls.size()];
        int i = 0;
        for (tmpLine v: ls) {
            this.lineSegments[i++] = new LineSegment(v.p, v.e);
        }
    }

    private class tmpLine {
        Point p;
        Point e;
        double slope;
    }

    private void pr(ArrayList<tmpLine> l) {
        StdOut.println(">--");
        for (tmpLine v: l) {
            StdOut.println(new LineSegment(v.p, v.e));
        }
        StdOut.println("<--");
    }

    private void swap(Point p1, Point p2) {
        StdOut.print(p1);
        StdOut.print(p2);
        StdOut.println("swap");
        Point tmp = p1;
        p1 = p2;
        p2 = tmp;
    }

    private boolean less(Point p1, Point p2) {
        StdOut.print(p1);
        StdOut.print("<");
        StdOut.print(p2);
        StdOut.println(p1.compareTo(p2) < 0);
        return p1.compareTo(p2) < 0;
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

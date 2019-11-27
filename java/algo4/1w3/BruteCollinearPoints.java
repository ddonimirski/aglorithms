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

        int mllsSize = 0;
        LineSegment[] mlls = new LineSegment[2];
        Point p, q, tmp;
        for (int i = 0; i < points.length; ++i) {
            p = points[i];
            for (int j = i; j < points.length; ++j) {
                q = points[j];
                double slope = p.slopeTo(q);
                if (slope == Double.NEGATIVE_INFINITY)
                    continue;
                if (p.compareTo(q) < 0)
                {
                    tmp = p;
                    p = q;
                    q = tmp;
                }

                for (int k = j ; k< points.length; ++k)
                {
                    tmp = points[k];
                    double slop2 = p.slopeTo(tmp);
                    if (slop2 != slope)
                        continue;
                    if (q.compareTo(tmp) < 0)
                        q = tmp;
                    else if (p.compareTo(tmp) > 0)
                        p = tmp;
                    else 
                        continue;

                    LineSegment ls_tmp = null;
                    for (int l = k; l < points.length; ++l) {
                        tmp = points[l];
                        slop2 = p.slopeTo(q);
                        if (slop2 != slope)
                            continue;
                        if (q.compareTo(tmp) < 0)
                            q = tmp;
                        else if (p.compareTo(tmp) > 0)
                            p = tmp;
                        else 
                            continue;

                        ls_tmp = new LineSegment(p, q);
                    }

                    if (ls_tmp != null) {
                        String ls_s = ls_tmp.toString();
                        if (mllsSize == mlls.length) {
                            LineSegment[] lss = new LineSegment[2*(mllsSize)];
                            for (int id = 0; id < mllsSize; ++id)
                                lss[id] = mlls[id];
                            mlls = lss;
                        }
                        boolean found = false;
                        for (int id = 0; id < mllsSize; ++id)
                        {
                            if (mlls[id].toString() == ls_s) {
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                            mlls[mllsSize++] = ls_tmp;
                    }
                }
            }
        }

        this.lineSegments = new LineSegment[mllsSize];
        copy(mlls, this.lineSegments);
    }

    private void copy(LineSegment[] src, LineSegment[] dst) {
        for (int i = 0; i < dst.length; ++i) {
            dst[i] = src[i];
        }
    }


    public int numberOfSegments() {       // the number of line segments
        return this.lineSegments.length;
    }

    public LineSegment[] segments() {               // the line segments 
        return this.lineSegments;
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

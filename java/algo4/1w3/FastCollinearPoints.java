import java.util.HashMap;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdDraw;

public class FastCollinearPoints {

    private LineSegment[] lineSegments;

    private void print(Point[] points) {
        for (Point p: points) {
            StdOut.print(p);
            StdOut.print(' ');
        }
        StdOut.println();
    }

    private boolean less(Point l, Point r) {
        return l.compareTo(r) < 0;
    }

    public FastCollinearPoints(Point[] points) {     // finds all line segments containing 4 or more points
        if (points == null)
            throw new IllegalArgumentException("FastCollinearPoints has got null value");
        for (int i = 0; i < points.length; ++i) {
            if (points[i] == null)
                throw new IllegalArgumentException("FastCollinearPoints has got null value");
        }

        QuickSort.sort(points);
        HashMap<Double, LineSegment> mp = new HashMap<Double, LineSegment>();
        print(points);

        for (int i=0; i < points.length-2; ++i) {
            Point left = points[i];
            Point right = points[i+1];
            StdOut.print(left);
            StdOut.print(right);
            double slope = left.slopeTo(right);
            StdOut.print("slope:");
            StdOut.print(slope);
            //if (null != mp.get(slope))
            //{
            //    StdOut.println("skiped");
            //    continue;
            //}
            int c = 2;
            for (int j = i+2; j < points.length; ++j) {
                Point tmp = points[j];
                double slope_tmp = left.slopeTo(tmp);
                if (slope != slope_tmp) continue;
                StdOut.print(" slope_tmp:");
                StdOut.print(slope_tmp);
                right = tmp;
                c++;
                StdOut.print(right);
                StdOut.print(c);
            }
            StdOut.print(c);
            if (c >= 4) {
                StdOut.println("add");
                mp.put(slope, new LineSegment(left, right));
            }
            else {
                StdOut.println();
            }
        }

        StdOut.println(mp.size());

        this.lineSegments = new LineSegment[mp.values().size()];
        int i = 0;
        for (LineSegment ls: mp.values()) {
            this.lineSegments[i++] = ls;
        }

        

    }

    private void print(LineSegment[] ls) {
        for (LineSegment v: ls) {
            StdOut.println(v);
        }
    }

    public           int numberOfSegments() {       // the number of line segments
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

        //// draw the points
        //StdDraw.enableDoubleBuffering();
        //StdDraw.setXscale(0, 32768);
        //StdDraw.setYscale(0, 32768);
        //for (Point p : points) {
        //    p.draw();
        //}
        //StdDraw.show();

        // print and draw the line segments
        FastCollinearPoints collinear = new FastCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            //segment.draw();
        }
        //StdDraw.show();
    }
}

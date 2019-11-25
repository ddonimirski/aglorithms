public class BruteCollinearPoints {

    private LineSegment[] lineSegments;

    public BruteCollinearPoints(Point[] points) {   // finds all line segments containing 4 points
        if (points == null)
            throw new IllegalArgumentException("BruteCollinearPoints has got null value");

        for (int i = 0; i < points.length; ++i) {
            if (points[i] == null)
                throw new IllegalArgumentException("Points should not have nulls points");
        }

        int lineSegmentsSize = 0;
        lineSegments = null;
        for (int i = 0; i < points.length; ++i) {
            Point p = points[i];
            for (int j = i; i < points.length; ++j) {
                Point q = points[j];
                double slope = p.slopeTo(q);
                if (slope == Double.NEGATIVE_INFINITY)
                    continue;
                if (p.compareTo(q) > 0)
                {
                    Point tmp = p;
                    p = q;
                    q = tmp;
                }

                for (int k = j ; k< points.length; ++k)
                {
                    Point t = points[k];
                    double slop2 = p.slopeTo(q);
                    if (slop2 != slope)
                        continue;
                    if (q.compareTo(t) > 0)
                        q = t;
                    else if (p.compareTo(t) > 0)
                        p = t;
                    else 
                        continue;

                    LineSegment tmp = null;
                    for (int l = k; l < points.length; ++l) {
                        t = points[l];
                        slop2 = p.slopeTo(q);
                        if (slop2 != slope)
                            continue;
                        if (q.compareTo(t) > 0)
                            q = t;
                        else if (p.compareTo(t) > 0)
                            p = t;
                        else 
                            continue;

                        tmp = new LineSegment(p, q);
                    }

                    if (tmp != null) {
                        if (lineSegmentsSize == 0 || lineSegmentsSize == lineSegments.length) {
                            LineSegment[] lss = new LineSegment[2*(lineSegmentsSize+1)];
                            for (int id = 0; id < lineSegmentsSize; ++id)
                                lss[id] = lineSegments[id];
                            lineSegments = lss;
                            lineSegmentsSize++;
                        }
                    }
                }
            }
        }
    }

    public           int numberOfSegments() {       // the number of line segments
        return this.lineSegments.length;
    }

    public LineSegment[] segments() {               // the line segments 
        return this.lineSegments;
    }
}

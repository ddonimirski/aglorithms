public class BruteCollinearPoints {

    private LineSegment[] lineSegments;;

    public BruteCollinearPoints(Point[] points) {   // finds all line segments containing 4 points
        if (points == null)
            throw new IllegalArgumentException("BruteCollinearPoints has got null value");
    }

    public           int numberOfSegments() {       // the number of line segments
        return this.lineSegments.length;
    }

    public LineSegment[] segments() {               // the line segments 
        return this.lineSegments;
    }
}

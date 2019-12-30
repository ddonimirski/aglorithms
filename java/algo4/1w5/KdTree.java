import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;
import java.util.LinkedList;
import java.util.List;


public class KdTree {

    private enum Separator { VERTICAL, HORIZONTAL }
    private Node root;
    private int size;

    private class Node {
        private static final double PEN_POINT = 0.005;
        private static final double PEN_LINE = 0.002;
        private final Separator sep;
        private final RectHV rect;
        private final Point2D point;
        private Node leftBottom;
        private Node rightTop;

        Node(Point2D p, Separator s, RectHV r) {
            this.point = p;
            this.sep = s;
            this.rect = r;
        }


        public Separator nextSep() {
            return sep == Separator.VERTICAL
                ? Separator.HORIZONTAL
                : Separator.VERTICAL;
        }

        public RectHV rectLB() {
            return sep == Separator.VERTICAL
                ? new RectHV(rect.xmin(), rect.ymin(), point.x(), rect.ymax())
                : new RectHV(rect.xmin(), rect.ymin(), rect.xmax(), point.y());
        }

        public RectHV rectRT() {
            return sep == Separator.VERTICAL
                ? new RectHV(point.x(), rect.ymin(), rect.xmax(), rect.ymax())
                : new RectHV(rect.xmin(), point.y(), rect.xmax(), rect.ymax());
        }

        public boolean isRightOrTop(Point2D p) {
            return (sep == Separator.HORIZONTAL && point.y() > p.y())
                || (sep == Separator.VERTICAL && point.x() > p.x());
        }

        public void draw() {
            StdDraw.setPenRadius(PEN_LINE);
            if (sep == Separator.VERTICAL) {
                StdDraw.setPenColor(StdDraw.RED); 
                StdDraw.line(point.x(), rect.ymin(), point.x(), rect.ymax());
            } else {
                StdDraw.setPenColor(StdDraw.BLUE); 
                StdDraw.line(rect.xmin(), point.y(), rect.xmax(), point.y());
            }

            StdDraw.setPenRadius(PEN_POINT);
            StdDraw.setPenColor(StdDraw.BLACK); 
            point.draw();
        }
    }


    public KdTree() {
        root = null;
        size = 0;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int size() {
        return size;
    }

    private void checkNull(Object obj) {
        if (obj == null)
            throw new IllegalArgumentException();
    }

    public void insert(Point2D p) {
        checkNull(p);

        if (root == null) {
            root = new Node(p, Separator.VERTICAL, new RectHV(0, 0, 1, 1));
            size++;
            return;
        }

        Node prev = null;
        Node curr = root;

        do {
            if (curr.point.equals(p)) return;

            prev = curr;
            curr = curr.isRightOrTop(p) ? curr.leftBottom : curr.rightTop;
        } while (curr != null);

        if (prev.isRightOrTop(p)) {
            prev.leftBottom = new Node(p, prev.nextSep(), prev.rectLB());
        } else {
            prev.rightTop = new Node(p, prev.nextSep(), prev.rectRT());
        }
        size++;
    }

    public boolean contains(Point2D p) {
        checkNull(p);
        Node node = root;
        while (node != null) {
            if (node.point.equals(p)) {
                return true;
            }
            node = node.isRightOrTop(p) ? node.leftBottom : node.rightTop;
        }

        return false;
    }

    public void draw() {
        if (root != null) 
            innerDraw(root);
    }

    private static void innerDraw(Node head) {
        head.draw();
        if (head.leftBottom != null) innerDraw(head.leftBottom);
        if (head.rightTop != null) innerDraw(head.rightTop);
    }

    public Iterable<Point2D> range(RectHV rect) {
        checkNull(rect);
        List<Point2D> res = new LinkedList<>();
        addAll(root, rect, res);
        return res;
    }


    private void addAll(Node node, RectHV rect, List<Point2D> res) {
        if (node == null) return;

        if (rect.contains(node.point)) {
            res.add(node.point);
            addAll(node.leftBottom, rect, res);
            addAll(node.rightTop, rect, res);
            return;
        }

        if (node.isRightOrTop(new Point2D(rect.xmin(), rect.ymin()))) {
            addAll(node.leftBottom, rect, res);
        } else {
            addAll(node.rightTop, rect, res);
        }
    }

    public Point2D nearest(Point2D p) {
        checkNull(p);
        return isEmpty() ? null : nearest(p, root.point, root);
    }

    private Point2D nearest(Point2D target, Point2D closest, Node node) {
        if (node == null) return closest;

        double closestDist = closest.distanceTo(target);
        if (node.rect.distanceTo(target) < closestDist) {
            double nodeDist = node.point.distanceTo(target);
            if (nodeDist < closestDist) {
                closest = node.point;
            }

            if (node.isRightOrTop(target)) {
                closest = nearest(target, closest, node.leftBottom);
                closest = nearest(target, closest, node.rightTop);
            } else {
                closest = nearest(target, closest, node.rightTop);
                closest = nearest(target, closest, node.leftBottom);
            }
        }

        return closest;
    }


    public static void main(String[] args) {
        // no unit tests so far
    }
}

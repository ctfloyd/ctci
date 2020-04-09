import java.util.HashSet;
import java.util.Random;

public class Exercise {

    public static final float NANO = 1000000000.0f;

   private static class Node {
        public Integer data;
        public Node next;

        public Node(int data) {
            this.data = data;
            this.next = null;
        }

        public Node() { this.data = null; this.next = null; }
    }


    public static void removeDuplicatesHash(Node list) {
        HashSet<Integer> table = new HashSet<>();
        Node current = list;
        Node previous = null;
        while(current != null) {
            if(table.contains(current.data)) {
                previous.next = current.next;
            } else {
                table.add(current.data);
                previous = current;
            }
            current = current.next;
        }
    }

    public static void removeDuplicatesRunner(Node list) {
        Node current = list;
        while(current != null) {
            Node runner = current;
            while(runner.next != null) {
                if(runner.next.data == current.data) {
                    runner.next = runner.next.next;
                } else {
                    runner = runner.next;
                }
            }
            current = current.next;
        }
    }

    public static Node makeList(int size) {
        Random r = new Random();
        Node root = new Node(r.nextInt(size - 1));
        Node current = root;
        for(int i = 0; i < size - 1; i++) {
            current.next = new Node(r.nextInt(size - 1));
            current = current.next;
        }
        return root;
    }

    public static void printList(Node list) {
        System.out.print("[");
        while(list.next != null) {
            System.out.print(list.data + ", ");
            list = list.next;
        }
        System.out.print(list.data);
        System.out.println("]");
    }

    public static void main(String[] args) {
        Node list1 = makeList(50000);
        System.out.println("Starting hashtable method");
        long now = System.nanoTime();
        removeDuplicatesHash(list1);
        long delta = System.nanoTime();
        System.out.println((delta - now) / NANO);
        Node list2 = makeList(50000);
        System.out.println("Starting runner method");
        now = System.nanoTime();
        removeDuplicatesRunner(list2);
        delta = System.nanoTime();
        System.out.println((delta - now) / NANO);
    }
}


import java.util.Random;

public class Exercise {

	static class Node {
		int data;
		Node next;

		public Node(int data) {
			this.data = data;
		}
	}
	
	public static Node sum(Node listOne, Node listTwo) {
        Node digitOne = listOne;
        Node digitTwo = listTwo;
        Node ret = null;
        Node head = null;
        int carry = 0;
        while(digitOne != null && digitTwo != null) {
            int one = digitOne.data;
            int two = digitTwo.data;
            int listValue = (one + two) % 10 + carry;
            carry = (one + two) / 10;
            if(ret == null) {
                ret = new Node(listValue);
                head = ret;
            } else {
                ret.next = new Node(listValue);
                ret = ret.next;
            }
            digitOne = digitOne.next;
            digitTwo = digitTwo.next;
        }
        return head;
    }

	public static void printList(Node head) {
		Node current = head;
		System.out.print("{");
		while(current != null) {
			System.out.print(" " + current.data);
			current = current.next;
		}
		System.out.println("}");
	}
	
	public static void main(String[] args) {
		
        Node head = new Node(7);
        head.next = new Node(1);
        head.next.next = new Node(6);

        Node two = new Node(5);
        two.next = new Node(9);
        two.next.next = new Node(2);
        
        Node result = sum(head, two);
        printList(result);
        
		

	}

}

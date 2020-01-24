

The following function just prints the nodes except the ones which are canceled out, you can make it push to a new list and return.

void printExCancel( node* head )
{
    node* start = head;
    node* end;

    while ( start )
    {
        bool mod = false;
        int sum = 0;
        end = start;
        while ( end )
        {
            sum += end->data;
            if ( sum == 0 )
            {
                start = end;
                mod = true;
                break;
            }
            end = end->next;
        }
        if ( mod == false ) {
            //push to new list
            printf( "%d\n", start->data );
        }
        //else {
        //    call funtion to delete from start to end
        //}
        start = start->next;
    }
}

or


Assumption: Only consecutive elements when summed to zero can be removed.
Approach Followed:
  1. Push the non-zero elements of the link list to a stack.
  2. On occurrence of a non zero element:
         (a) Iterate stack, pop each element and keep adding to the non-zero element.
         (b) Keep adding the pop element to a list.
         (c) If the value is zero (that means then by now you have removed ) break stack iteration.
         (d) If stack is Empty & the sum != 0 add the list elements to stack along with the non-zero one

Try Following Code:

    public class ElementSumNonZero {

    private static Node head;

    private static class Node {
        int data;
        Node next;

        Node(int d) {
            data = d;
            next = null;
        }
    }

    private void removeNonZeroElements(Node root) {
     Node start = root;
     Stack<Node> stack = new Stack<>();
     boolean flag = false;
     List<Node> list = new ArrayList<>();
     while (start != null) {
        if (start.data > 0)
            stack.push(start);
        else {
            int sum = start.data;
            flag = false;
            while (!stack.isEmpty()) {
                Node temp = stack.pop();
                sum += temp.data;
                if (sum == 0) {
                    flag = true;
                    list.clear();
                    break;
                }
                list.add(temp);
            }
            if (!flag) {
                list.forEach(i -> stack.add(i));
                stack.add(start);
            }
        }
        start = start.next;
     }
     stack.forEach(i -> System.out.print(i.data +" -> "));
     System.out.println("NULL");
   }

    // Driver program to test above functions
    public static void main(String[] args) {
        ElementSumNonZero list = new ElementSumNonZero();
        ElementSumNonZero.head = new Node(6);
        ElementSumNonZero.head.next = new Node(-6);
        ElementSumNonZero.head.next.next = new Node(8);
        ElementSumNonZero.head.next.next.next = new Node(4);
        ElementSumNonZero.head.next.next.next.next = new Node(-12);
        ElementSumNonZero.head.next.next.next.next.next = new Node(9);
        ElementSumNonZero.head.next.next.next.next.next.next = new Node(8);
        ElementSumNonZero.head.next.next.next.next.next.next.next = new Node(-8);

        list.removeNonZeroElements(head);
    }
}

Test 0
original: {6, -6,6, 8, 4, -12, 9, 8, -8}
canceled out: {9}

Test 1
original: {4, 6, -10, 8, 9, 10, -19, 10, -18, 20, 25}
canceled out: {20, 25}

We can create the resultant stack into a link list and return from "removeNonZeroElements" method.
Please correct me and suggest ways we can make this code efficient.


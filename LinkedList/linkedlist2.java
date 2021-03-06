import java.util.ArrayList;

public class question {

    public class ListNode {
        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
        }
    }

    public ListNode midNode(ListNode node) {
        if (node == null || node.next == null)
            return node;

        ListNode slow = node, fast = node;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // leetcode 876:
    public ListNode middleNode(ListNode node) {
        if (node == null || node.next == null)
            return node;

        ListNode slow = node, fast = node;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }

    // leetcode 206:

    public ListNode reverseList(ListNode node) {
        if (node == null || node.next == null)
            return node;

        ListNode prev = null;
        ListNode curr = node;
        while (curr != null) {
            ListNode forw = curr.next; // backup.

            curr.next = prev; // connection

            prev = curr; // move forw.
            curr = forw;
        }

        return prev;
    }

    // leetcode 234.=======================================

    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null)
            return true;

        ListNode mid = midNode(head);
        ListNode nhead = mid.next;
        mid.next = null;

        nhead = reverseList(nhead);

        ListNode c1 = head, c2 = nhead;
        boolean res = true;

        while (c1 != null && c2 != null) {
            if (c1.val != c2.val) {
                res = false;
                break;
            }
            c1 = c1.next;
            c2 = c2.next;
        }

        nhead = reverseList(nhead);
        mid.next = nhead;

        return res;
    }

    // Leetcode 143.
    public void reorderList(ListNode head) {
        if (head == null || head.next == null)
            return;

        ListNode mid = midNode(head);
        ListNode nhead = mid.next;
        mid.next = null;

        nhead = reverseList(nhead);
        ListNode c1 = head, c2 = nhead;

        while (c1 != null && c2 != null) {
            ListNode f1 = c1.next, f2 = c2.next; // backup

            c1.next = c2; // connection.
            c2.next = f1;

            c1 = f1; // move forward.
            c2 = f2;
        }
    }

    // Leetcode 19:
    public ListNode removeNthFromEnd(ListNode head, int n) { // min possible value of n : 1 and it is always valid.
        if (head == null || head.next == null)
            return null;

        ListNode c1 = head, c2 = head;
        while (n-- > 0)
            c2 = c2.next;

        if (c2 == null) // if we have to remove head.
            return head.next;

        while (c2.next != null) {
            c1 = c1.next;
            c2 = c2.next;
        }

        ListNode rnode = c1.next;
        c1.next = rnode.next;
        rnode.next = null;

        // delete rnode; // for c++.

        return head;
    }

    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null)
            return l1 == null ? l2 : l1;

        ListNode head = new ListNode(-1); // dummy Node.
        ListNode prev = head;

        ListNode c1 = l1, c2 = l2;
        while (c1 != null && c2 != null) {
            if (c1.val <= c2.val) {
                prev.next = c1;
                prev = c1;
                c1 = c1.next;
            } else {
                prev.next = c2;
                prev = c2;
                c2 = c2.next;
            }
        }

        if (c2 != null)
            prev.next = c2;
        else
            prev.next = c1;

        return head.next;
    }

    // Leetcode 023.
    public ListNode mergeKLists(ListNode[] lists) { // O(KN).
        if (lists.length == 0)
            return null;
        ArrayList<ListNode> list = new ArrayList<>();
        for (int i = 0; i < lists.length; i++)
            list.add(lists[i]);

        while (list.size() != 1) {
            ListNode l1 = list.remove(list.size() - 1);
            ListNode l2 = list.remove(list.size() - 1);

            ListNode l3 = mergeTwoLists(l1, l2);
            list.add(l3);
        }

        return list.get(0);
    }

    public ListNode mergeKLists02(ListNode[] lists, int li, int ri) { // O(Nlogk)
        if (li == ri)
            return lists[li];

        int mid = (li + ri) / 2;

        ListNode l1 = mergeKLists02(lists, li, mid);
        ListNode l2 = mergeKLists02(lists, mid + 1, ri);
        ListNode finalList = mergeTwoLists(l1, l2);

        return finalList;
    }

    public ListNode mergeKLists02(ListNode[] lists) {
        if (lists.length == 0)
            return null;

        return mergeKLists02(lists, 0, lists.length - 1);
    }

}

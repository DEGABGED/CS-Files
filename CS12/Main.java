package cs12.me.list;

public class Main {
    public static void main(String[] args) {
        LinkedList list = new LinkedList();
        list.add(0, 1);
        list.add(0, 2);
        list.add(2, 3);
        list.add(3, 4);
        list.add(1, 5);
        list.add(3, 6);
        list.view();
        System.out.println(list.remove(0));
        System.out.println(list.remove(5));
        System.out.println(list.remove(2));
        list.view();
    }
}

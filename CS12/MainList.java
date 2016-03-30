package cs12.list;
import java.util.Scanner;
import java.io.*;

public class MainList {
	public static void main(String args[]) throws Exception {
		LinkedList list = new LinkedList();
		int ch = 0;
		Scanner sc = new Scanner(System.in);
		String[] input = new String[3];
		LinkedList[] split = new LinkedList[2];
		do {
			System.out.println("0: load from file\n1: save to file\n2: add to list\n3: remove from list\n4: print list\n5: sort list\n6: split list\n7: clear list\n8: add 2 lists\n9: quit");
			ch = sc.nextInt();
			String dump = sc.nextLine();
			switch(ch){
				case 0:
					System.out.println("Enter file path: ");
					list = loadFile(sc.nextLine(), list);
					break;
				case 1:
					System.out.println("Enter file path: ");
					saveFile(sc.nextLine(), list);
					break;
				case 2:
					System.out.println("Enter name, age, then course: ");
					input[0] = sc.nextLine();
					input[1] = sc.nextLine();
					input[2] = sc.nextLine();
					System.out.println("Enter index: ");
					list.add(new Student(input[0], Integer.parseInt(input[1]), input[2]), sc.nextInt());
					break;
				case 3:
					System.out.println("Enter index: ");
					list.remove(sc.nextInt());
					break;
				case 4:
					System.out.println(list);
					break;
				case 5:
					list.qsort();
					break;
				case 6:
					System.out.println("Enter the index: ");
					split = list.split(sc.nextInt());
					System.out.println("List 1: \n" + split[0]);
					System.out.println("List 2: \n" + split[1]);
					break;
				case 7:
					list.clear();
					break;
				case 8:
					System.out.println("Choose a list source: ");
					list = list.addAll(loadFile(sc.nextLine(), new LinkedList()));
					break;
				case 9: break;
			}
		} while(ch != 9);
	}

	private static LinkedList loadFile(String path, LinkedList list) throws Exception {
		BufferedReader sc = new BufferedReader(new FileReader(path));
		list = new LinkedList();
		int size = 0;
		String[] input = new String[3];
		input[0] = sc.readLine();
		input[1] = sc.readLine();
		input[2] = sc.readLine();
		while(input[0] != null) {
			list.add(new Student(input[0], Integer.parseInt(input[1]), input[2]), size);
			size++;
			input[0] = sc.readLine();
			input[1] = sc.readLine();
			input[2] = sc.readLine();
		}
		return list;
	}

	private static void saveFile(String path, LinkedList list) throws Exception {
		PrintWriter pw = new PrintWriter(path);
		pw.print(list.toStringRaw());
		pw.close();
	}
}

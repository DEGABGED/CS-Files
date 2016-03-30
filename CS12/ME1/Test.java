package me1.delacruz;
import java.util.Scanner;

public class Test {
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		LinkedStack stack = new LinkedStack();
		int input = 0;
		do {
			System.out.println("1: Add; 2: Peek; 3: Pop; 4: Clear; 5: View; 6: IsEmpty");
			input = sc.nextInt();
			switch(input){
				case 1:
					System.out.print("Enter a word: ");
					stack.push(sc.next());
					break;
				case 2:
					System.out.println(stack.peek());
					break;
				case 3:
					System.out.println(stack.pop());
					break;
				case 4:
					stack.clear();
					break;
				case 5:
					System.out.println(stack);
					break;
				case 6:
					System.out.println(stack.isEmpty() ? "Yes" : "No");
					break;
				default:
					break;
			}
		} while(input != 0);
	}
}

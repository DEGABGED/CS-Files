package me1.delacruz;
import java.util.Scanner;

public class Test {
	private LinkedStack stack1;

	public Test() {
		stack1 = new LinkedStack();
		stack1.push("First");
		stack1.push("Second");
		stack1.push("Third");
	}

	public LinkedStack getStackRev() {
		return this.stack1.getReverse();
	}
	public LinkedStack getStack() { return this.stack1; }
}

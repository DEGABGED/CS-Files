package me1.delacruz;

/**
* <h1>LinkedStack</h1>
* The LinkedStack class is a LinkedList interpretation of the Stack data structure.
*
* @author	Francis Zac dela Cruz
* @since	2015-03-26
*/

public class LinkedStack {

	/**
	* <h1>Node</h1>
	* The Node class is a private class. The Node object is a component of the
	* LinkedStack object;
	*
	* @author	Francis Zac dela Cruz
	* @since	2015-03-26
	*/
	private class Node {
		public Object data;
		public Node link;
		public String toString() { return data.toString(); }
	}

	private Node top;
	private int size;

	/**
	* This constructor creates an empty linked stack.
	*/
	public LinkedStack() {
		this.top = null;
		this.size = 0;
	}

	/**
	* Accessor method for private attribute size
	* @return Size of the stack.
	*/
	public int getSize() { return this.size; }

	/**
	* Pushes an Object on the top of the stack.
	* @param x Object to be pushed
	*/
	public void push(Object x) {
		Node pushed = new Node();
		pushed.data = x;
		pushed.link = top;
		this.top = pushed;
		this.size++;
	}

	/**
	* Returns and removes the Object at the top of the stack. Returns
	* null if the stack is empty.
	* @return Object at the top of the stack.
	*/
	public Object pop() {
		if(this.isEmpty()) return null;
		Node popped = this.top;
		this.top = this.top.link;
		this.size--;
		return popped.data;
	}

	/**
	* Returns but does not remove the Object at the top of the stack.
	* Returns null if the stack is empty.
	* @return Object at the top of the stack.
	*/
	public Object peek() {
		return this.isEmpty() ? null : this.top.data;
	}

	/**
	* Returns a boolean value of whether or not the stack is empty.
	* @return Whether or not stack is empty.
	*/
	public boolean isEmpty() {
		return this.top == null;
	}

	/**
	* Clears the stack. The top and size are simply reset, and the Java
	* garbage collection handles the rest.
	*/
	public void clear() {
		this.top = null;
		this.size = 0;
	}

	/**
	* Reverses the order of the stack, by creating a new stack and
	* pushing all the contents popped from this stack.
	*/
	public void reverse() {
		if(this.isEmpty()) return;
		LinkedStack tmp = new LinkedStack();
		while(!this.isEmpty()) { tmp.push(this.pop()); }
		this.top = tmp.top;
		this.size = tmp.size;
	}

	/**
	* Reverses the order of the stack, by creating a new stack and
	* pushing all the contents popped from this stack.
	* Unlike the other reverse function, this one returns a new
	* stack, while not changing the old one.
	*/
	public LinkedStack getReverse() {
		if(this.isEmpty()) return null;
		LinkedStack o = new LinkedStack();
		Node ptr = this.top;
		for(;ptr != null;ptr = ptr.link) o.push(ptr.data);
		return o;
	}

	/**
	* Converts the LinkedStack to a string for output.
	* @return String representation of the stack.
	*/
	public String toString() {
		if(this.isEmpty()) return "xxxxx\n";
		String output = "";
		//output += "" + this.size + " items: {";
		for(Node ptr = this.top; ptr != null; ptr = ptr.link) {
			output += (ptr == this.top ? "" : "-") + "[" + ptr.data + "]";
		}
		output +=  "\n";
		return output;
	}

	/**
	* Converts the LinkedStack to a string for file output. This method only works
	* for Card piles / LinkedStacks of Cards.
	* @return String representation of the stack.
	*/
	public String toRawString() {
		if(this.isEmpty()) return "000\n";
		String output = "";
		for(Node ptr = this.top; ptr != null; ptr = ptr.link) {
			output += ((Card) ptr.data).toRawString();
		}
		return output;
	}
}

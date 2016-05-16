package me1.delacruz;

public class Deck extends LinkedStack<Card> {
	public Deck() {
		super();
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
			output += ptr.data.toRawString();
		}
		return output;
	}

	/**
	* Reverses the order of the stack, by creating a new stack and
	* pushing all the contents popped from this stack.
	* Unlike the other reverse function, this one returns a new
	* stack, while not changing the old one.
	*/
	@Override
	public Deck getReverse() {
		if(this.isEmpty()) return null;
		Deck o = new Deck();
		Node ptr = this.top;
		for(;ptr != null;ptr = ptr.link) o.push(ptr.data);
		return o;
	}
}

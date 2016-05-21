package mp1.delacruz;

/**
* <h1>Deck</h1>
* The Deck class extends a Card LinkedStack, and utilizes a toRawString() method
* which allows the deck to be saved to a file.
*
* @author	Francis Zac dela Cruz
* @since	2015-05-18
*/
public class Deck extends LinkedStack<Card> {
	/**
	 * This constructor constructs the Deck object using the constructor for the LinkedStack with
	 * generic type Card.
	 */
	public Deck() {
		super();
	}

	/**
	* Converts the Deck to a string for file output.
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
	* Reverses the order of the deck, by creating a new deck and
	* pushing all the contents popped from this deck.
	* Unlike the other reverse function, this one returns a new
	* deck, while not changing the old one.
	* Overridden because a LinkedStack<Card> can't be converted
	* to a Deck.
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

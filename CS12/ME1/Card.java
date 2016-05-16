package me1.delacruz;

/**
* <h1>Card</h1>
* The Card class is a blueprint for a Card object, which includes its rank,
* suit, and state.
*
* @author	Francis Zac dela Cruz
* @since	2015-03-26
*/

public class Card {
	private Suit suit;
	private int rank;
	private boolean faceUp;

	/**
	* This constructor creates a Card object from a given rank and suit.
	* The state of the card is automatically faced down.
	* @param suit The assigned suit of the card.
	* @param rank The assigned rank of the card.
	*/
	public Card(Suit suit, int rank) {
		this.suit = suit;
		this.rank = rank;
		this.faceUp = false;
	}

	/**
	* This constructor creates a Card object from a string input. The card's suit,
	* rank and state is parsed from this string.
	* @param input The string where the Card's data is initially stored.
	*/
	public Card(String input) {
		String[] args = input.split("\t");
		this.rank = Integer.parseInt(args[0]);
		this.suit = Constant.SUITS[Integer.parseInt(args[1])];
		this.faceUp = args[2].equals("1");
	}

	/**
	* Accessor method for private attribute suit
	* @return Suit of the Card.
	*/
	public Suit getSuit() { return this.suit; }

	/**
	* Accessor method for private attribute rank
	* @return Rank of the Card.
	*/
	public int getRank() { return this.rank; }

	/**
	* Accessor method for private attribute faceUp
	* @return State of the Card.
	*/
	public boolean getFaceUp() { return this.faceUp; }

	/**
	* Mutator method for private attribute faceUp
	* @param up
	*/
	public void setFaceUp(boolean up) { this.faceUp = up; }

	/**
	* Converts the Card to a string for output.
	* @return String representation of the Card.
	*/
	public String toString() {
		if(!this.faceUp) return "***";
		String output = "";
		switch(this.rank) {
			case 1: output += "A"; break;
			case 11: output += "J"; break;
			case 12: output += "Q"; break;
			case 13: output += "K"; break;
			default: output += this.rank;
		}
		switch(this.suit) {
			case SPADES: output += Constant.SPDS; break;
			case HEARTS: output += Constant.HRTS; break;
			case DIAMONDS: output += Constant.DMND; break;
			case CLUBS: output += Constant.CLBS; break;
		}
		output += (this.rank == 10 ? "" : " ") + "";
		return output;
	}

	/**
	* Converts the Card to a string for file output.
	* @return String representation of the Card.
	*/
	public String toRawString() {
		int suitndx = 0;
		switch(this.suit) {
			case HEARTS: suitndx = 1; break;
			case DIAMONDS: suitndx = 2; break;
			case CLUBS: suitndx = 3; break;
		}
		return "" + this.rank + "\t" + suitndx + "\t" + (this.faceUp ? "1" : "0") + "\n";
	}
}

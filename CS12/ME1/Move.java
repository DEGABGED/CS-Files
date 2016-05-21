package me1.delacruz;

/**
* <h1>Move</h1>
* The Move object contains data about a move performed by the user.
* Examples include flipping a card, drawing, throwing, moving between
* tableus, etc.
*
* Legend:
* -1: Empty / Invalid
* 0: Stock
* 1: Talon
* 2: Hand
* 3-6: Foundations
* 7-13: Tableus
* Note: To denote a top card flip, both src and dest piles would be equal,
*   and the cardsMoved will be 1 or 0 depending on whether the card was
*   flipped up or down.
* Move index indicates groups of moves (eg. a chain of moves which move cards
*   between tableus will be under 1 index)
*
* @author	Francis Zac dela Cruz
* @since	2015-05-18
*/
public class Move {
	private int srcPile;
	private int destPile;
	private int cardsMoved;
	private int moveIndex;

	/**
	 * This constructor creates a Move object with a source pile index,
	 * destination pile index, a card count, and a move index.
	 * @param src The source pile.
	 * @param dest The destination pile.
	 * @param count The number of cards to be moved.
	 * @param ndx The move index.
	 */
	public Move(int src, int dest, int count, int ndx) {
		this.srcPile = src;
		this.destPile = dest;
		this.cardsMoved = count;
		this.moveIndex = ndx;
	}

	/**
	* Accessor method for private attribute srcPile.
	* @return Source pile.
	*/
	public int getSrc() { return this.srcPile; }

	/**
	* Accessor method for private attribute destPile.
	* @return Destination pile.
	*/
	public int getDest() { return this.destPile; }

	/**
	* Accessor method for private attribute cardsMoved.
	* @return Number of cards moved.
	*/
	public int getCount() { return this.cardsMoved; }

	/**
	* Accessor method for private attribute moveIndex.
	* @return Move index.
	*/
	public int getIndex() { return this.moveIndex; }

	/**
	* Returns a string representation of the moves.
	* For debugging.
	* @return String representation of the move.
	*/
	public String toString() {
		return "<"+this.moveIndex+": "+this.srcPile+","+this.destPile+","+this.cardsMoved+">";
	}
}

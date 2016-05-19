package me1.delacruz;

/**
* <h1>SolitaireWrapper</h1>
* The SolitaireWrapper class extends the Solitaire class and adds general
* purpose card movement between piles. The same system for indexing card piles
* as in the Move class is used.
*
* @author	Francis Zac dela Cruz
* @since	2015-05-18
*/
public class SolitaireWrapper extends Solitaire {
	/**
 	 * This constructor invokes its parent's constructor.
 	 */
	public SolitaireWrapper() {
		super();
	}

	/**
	 * This method moves a group of cards across tableus.
	 * @param srcPile The source pile.
	 * @param destPile The destination pile.
	 * @param amount The amount of cards to be moved.
	 * @return Whether or not the move was successful.
	 */
	public boolean moveMultipleCards(int srcPile, int destPile, int amount) {
		if (srcPile < 7 || srcPile >= 14 || destPile < 7 || destPile >= 14) return false;

		// Get from srcPile to hand
		this.hand = this.getFromTableu(srcPile-7, amount);
		if (this.hand == null) {
			this.hand = new Deck();
			return false;
		}

		// Move from hand to destPile
		int i = 0;
		for (; i<amount; i++) {
			if (this.hand.isEmpty()) break;
			if (!this.moveToTableu((this.hand.peek()), destPile-7)) {
				// Undo
				while (i >= 0) {
					if (i == 1) this.undo(); // Tableu opening
					this.undo();
					i--;
				}
				return false;
			}
			this.hand.pop();
		}

		return true;
	}

	/**
	 * This method moves a single card between the talon, stock, foundation,
	 * or tableus.
	 * @param srcPile The source pile.
	 * @param destPile The destination pile.
	 * @return Whether or not the move was successful.
	 */
	public boolean moveSingleCard(int srcPile, int destPile) {
		if (srcPile == 2 || destPile == 2) return false; // This method is supposed to skip the hand
		if (srcPile <= 0 || srcPile >= 14 || destPile <= 0 || destPile >= 14) return false; // You cannot move move or to the stock directly

		// Get from srcPile to hand
		switch (srcPile) {
			case 1:
				this.hand.push(this.getFromTalon());
				break;
			case 3:
			case 4:
			case 5:
			case 6:
				if(!this.foundations[srcPile-3].isEmpty()) {
					this.hand.push(this.getFromFoundation(Constant.SUITS[srcPile-3]));
					break;
				} else {
					return false;
				}
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
				this.hand = this.getFromTableu(srcPile-7, 1);
				if(this.hand == null) {
					this.hand = new Deck();
					return false;
				}
				break;
			default:
				return false;
		}

		// Double check if hand is null or empty
		if (hand == null || hand.isEmpty()) return false;

		// Move from hand to destPile
		// At this part, start this.undo()-ing shit if mistakes start happening
		switch (destPile) {
			case 1:
				this.throwAway(this.hand.pop());
				return true;
			case 3:
			case 4:
			case 5:
			case 6:
				if(this.moveToFoundation(this.hand.peek())) {
					// Success
					this.hand.pop();
					return true;
				} else {
					// Failure; return the cards
					this.undo(); // Undo moving cards from tableu to hand
					return false;
				}
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
				if(this.moveToTableu(this.hand.peek(), destPile-7)) {
					// Success
					this.hand.pop();
					return true;
				} else {
						// Failure
					this.undo(); // Undo moving card from src to hand
					return false;
				}
			default:
				return false;
		}
	}

	/**
	 * This method undoes a group of moves. Groups of moves are determined
	 * according to move index.
	 */
	public void undoGroup() {
		if (this.moves.isEmpty()) return;
		int lastMove = this.moves.peek().getIndex();
		while(!this.moves.isEmpty() && this.moves.peek().getIndex() == lastMove) {
			this.undo();
		}
		this.moveCount++;
	}
}

package me1.delacruz;

public class SolitaireWrapper extends Solitaire {
	public SolitaireWrapper() {
		super();
	}
	/*
		Some notes:
		- All openTableus() calls are in the Solitaire.java
	*/

	/**
	* The following method moves a card from a tableu to the foundation
	*/
	public boolean tableuToFoundation(int tableuPile, int foundationPile, int amount) {
		if(amount != 1) return false;
		else {
			// Attempt first
			this.hand = this.getFromTableu(tableuPile, 1);
			if(this.hand == null) {
				return false;
			}

			if(this.moveToFoundation((Card) this.hand.peek())) {
				// Success
				this.hand.pop();
				return true;
			} else {
				// Failure; return the cards
				this.undo(); // Undo moving cards from tableu to hand
				return false;
			}
		}
	}

	/**
	* This method moves a card from a foundation to a tableu
	*/
	public boolean foundationToTableu(int tableuPile, int foundationPile, int amount) {
		if(amount != 1) return false;
		else {
			if(!this.foundations[foundationPile].isEmpty()) {
				this.hand.push(this.getFromFoundation(Constant.SUITS[foundationPile]));
			}
			if(this.moveToTableu((Card) this.hand.peek(), tableuPile)) {
				// Success
				this.hand.pop();
				return true;
			} else {
				// Failure
				this.undo(); // Undo moving card from foundation to hand
				return false;
			}
		}
	}

	/**
	 * This method throws away a card from any of the piles
	 */

	/**
	 * This method moves a group of cards across tableus
	 */
	public boolean moveMultipleCards(int srcPile, int destPile, int amount) {
		if (srcPile < 7 || srcPile >= 14 || destPile < 7 || destPile >= 14) return false;

		// Get from srcPile to hand
		this.hand = this.getFromTableu(srcPile-7, amount);
		if (this.hand == null) {
			return false;
		}

		// Move from hand to destPile
		int i = 0;
		for (; i<amount; i++) {
			if (!this.moveToTableu(((Card) this.hand.peek()), destPile-7)) {
				// Undo
				while (i > 0) {
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
	* This method moves a single card from either the talon, foundation, or tableu, to any of the other three.
	*/
	public boolean moveSingleCard(int srcPile, int destPile) {
		if (srcPile == 2 || destPile == 2) return false; // This method is supposed to skip the hand
		if (srcPile < 0 || srcPile >= 14 || destPile < 0 || destPile >= 14) return false;

		// Get from srcPile to hand
		switch (srcPile) {
			case 0:
				return false; // You cannot get from the stock directly; you'd have to call draw()
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
				this.throwAway((Card) this.hand.pop());
				return true;
			case 3:
			case 4:
			case 5:
			case 6:
				if(this.moveToFoundation((Card) this.hand.peek())) {
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
				if(this.moveToTableu((Card) this.hand.peek(), destPile-7)) {
					// Success
					this.hand.pop();
					return true;
				} else {
						// Failure
					this.undo(); // Undo moving card from foundation to hand
					return false;
				}
			default:
				return false;
		}
	}

	public LinkedStack getPile(int pile) {
		switch (pile) {
			case 0: return this.stock;
			case 1: return this.talon;
			case 2: return this.hand;
			case 3:
			case 4:
			case 5:
			case 6: return this.foundations[pile-3];
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13: return this.tableu[pile-7];
			default: return null;
		}
	}
}

package me1.delacruz;
import java.io.*;
import java.util.Collections;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

/**
* <h1>Solitaire</h1>
* The Solitaire class holds a game object, responsible for holding the different
* card piles in the game, and interacting between them.
*
* @author	Francis Zac dela Cruz
* @since	2015-03-26
*/

public class Solitaire {
	private Card deck[] = new Card[52];
	private LinkedStack talon = new LinkedStack();
	private LinkedStack foundations[] = new LinkedStack[4];
	private LinkedStack stock = new LinkedStack();
	private LinkedStack tableu[] = new LinkedStack[7];
	private int redealsLeft = 3;

	/**
	* This constructor initializes the foundations and tableus, shuffles the deck,
	* and distributes the cards accordingly.
	*/
	public Solitaire() {
		for(int x=0; x<4; x++){
			this.foundations[x] = new LinkedStack();
		}
		for(int x=0; x<7; x++){
			this.tableu[x] = new LinkedStack();
		}
		for(int s=0; s<4; s++){
			for(int r=1; r<14; r++){
				this.deck[(s*13)+r-1] = new Card(Constant.SUITS[s], r);
			}
		}

		//Create the stock and tableus
		this.shuffle();
		this.deal();
	}

	/**
	* Flips up or down a Card. Since Cards popped / peeked from a
	* LinkedStack are of type Object, they would have to be typecasted. This method
	* simply prevents the writing of code similar to the following:
	*     ((Card) this.stock.peek()).setFaceUp(true)
	*/
	private void faceCard(Card card, boolean faceUp) { card.setFaceUp(faceUp); }

	/**
	* Checks if the suits of 2 cards alternate between black (Clubs,
	* Spades) and red (Hearts, Diamonds). If one of the cards is null (eg. comparing
	* a King of Spades with the top of a blank tableu), then this returns true.
	* @param ac First card.
	* @param bc Second card.
	* @return Whether or not the cards are of alternating suit.
	*/
	private boolean isAlternating(Card ac, Card bc) {
		if(ac == null || bc == null) return true;
		Suit a = ac.getSuit();
		Suit b = bc.getSuit();
		if((a == Constant.SUITS[0] || a == Constant.SUITS[3]) && (b == Constant.SUITS[1] || b == Constant.SUITS[2])) return true;
		if((b == Constant.SUITS[0] || b == Constant.SUITS[3]) && (a == Constant.SUITS[1] || a == Constant.SUITS[2])) return true;
		return false;
	}

	/**
	* Checks if the game's stock pile is empty. Accessed by the Main class.
	* @return Whether or not the stock is empty.
	*/
	public boolean isStockEmpty() { return this.stock.isEmpty(); }

	/**
	* Throws away a Card by moving it to the Talon pile.
	* @param card Card to be thrown.
	*/
	public void throwAway(Card card) { if(card != null) this.talon.push(card); }

	/**
	* Checks if the game is already won or not.
	* @return Whether or not the game is already won.
	*/
	public boolean isWin() {
		int total = 0;
		for(LinkedStack x : this.foundations){
			total += x.getSize();
		}
		return total == 52;
	}

	/**
	* Moves all Talon cards back to the Stock, while deducting from the total amount
	* of redeals left. Not to be confused with a reset.
	* @return Number of redeals left.
	*/
	public int redeal() {
		if(this.redealsLeft == 0) return -1;
		if(this.talon.isEmpty()) return redealsLeft;
		while(!this.talon.isEmpty()) {
			this.stock.push(this.talon.pop());
		}
		return --redealsLeft;
	}

	/**
	* Deals cards to the stock, then from the stock to the tableus.
	*/
	public void deal() {
		// Deal to the stock
		for(Card x : this.deck){
			this.stock.push(x);
		}

		// Deal to the tableus
		for(int x=0; x<7; x++){
			for(int y=x; y<7; y++){
				this.tableu[y].push(this.stock.pop());
				if(y==x){
					this.faceCard((Card) this.tableu[y].peek(), true);
				}
			}
		}

		this.faceCard((Card) this.stock.peek(), true);
	}

	/**
	* Shuffles the deck using the Collections.shuffle method.
	*/
	public void shuffle() {
		List<Card> decklist = new ArrayList<Card>(Arrays.asList(this.deck));
		Collections.shuffle(decklist);
		decklist.toArray(this.deck);
	}

	/**
	* Prints the stock, talon, foundations, tableus, and redeals left. Uses Unicode
	* characters.
	*/
	public void printGameState() {
		int b = 0;
		int fndtotal = 0;

		//Print Stock, Talon, and Foundations
		System.out.println(Constant.STFTOP);
		System.out.print(String.format(Constant.CARDTEXT, (Card) this.stock.peek() == null ? "   " : (Card) this.stock.peek()) +
			String.format(Constant.CARDTEXT, (Card) this.talon.peek() == null ? "   " : (Card) this.talon.peek()) + Constant.CARDWIDTH);
		for(LinkedStack x : this.foundations){
			System.out.print(String.format(Constant.CARDTEXT, (Card) x.peek() == null ? "   " : (Card) x.peek()));
			fndtotal += x.getSize();
		}
		System.out.print("\n");
		for(b=0; b<3; b++){
			System.out.println(Constant.STFBODY);
		}
		System.out.println(Constant.STFBOTTOM);

		//Print Labels
		System.out.println(" Stock  Talon " + Constant.CARDWIDTH +
			String.format(Constant.CARDMARGIN, Constant.SPDS) +
			String.format(Constant.CARDMARGIN, Constant.HRTS) +
			String.format(Constant.CARDMARGIN, Constant.DMND) +
			String.format(Constant.CARDMARGIN, Constant.CLBS));
		System.out.println(" Redeals left: " + this.redealsLeft +
			", Stock: " + this.stock.getSize() +
			", Foundations: " + fndtotal + "\n");
		for(int x=1; x<8; x++){
			System.out.print(String.format(Constant.CARDMARGIN, x));
		}
		System.out.print("\n");

		//Print Tableus
		LinkedStack[] tableuRev = new LinkedStack[7];
		for(b=0; b<7; b++){
			tableuRev[b] = new LinkedStack();
			while(!tableu[b].isEmpty()) tableuRev[b].push(tableu[b].pop());
		}

		boolean someRemain = true;
		while(someRemain){
			someRemain = false;
			for(b=0; b<7; b++){
				if(!tableuRev[b].isEmpty()){
					tableu[b].push(tableuRev[b].pop());
					System.out.print(String.format(Constant.CARDTOPTMPL, (Card) tableu[b].peek()));
					someRemain = true;
				} else  {
					System.out.print(Constant.CARDWIDTH);
				}
			}
			System.out.print("\n");
		}
	}

	/**
	* Draws a card from the stock.
	* @return Card drawn from the stock.
	*/
	public Card draw() {
		Card output = (Card) this.stock.pop();
		if(!this.stock.isEmpty()) this.faceCard((Card) this.stock.peek(), true);
		return output;
	}

	/**
	* Moves the Card to the corresponding foundation, but checks whether or not
	* it can be moved to a foundation in the first place.
	* @return Whether or not the card was successfully moved.
	*/
	public boolean moveToFoundation(Card card) {
		int pile = 0;
		if(card.getSuit() == Suit.HEARTS) pile = 1;
		else if(card.getSuit() == Suit.DIAMONDS) pile = 2;
		else if(card.getSuit() == Suit.CLUBS) pile = 3;

		if(this.foundations[pile].isEmpty() && card.getRank() != 1) return false;
		if(!this.foundations[pile].isEmpty() &&
			card.getRank() - ((Card) this.foundations[pile].peek()).getRank() != 1) return false;
		this.foundations[pile].push(card);
		return true;
	}

	/**
	* Moves the Card to a chosen tableu, but checks whether or not it can be moved
	* to the tableu in the first place.
	* @return Whether or not the card was successfully moved.
	*/
	public boolean moveToTableu(Card card, int pile) {
		if(!isAlternating(card, (Card) this.tableu[pile].peek())) return false;
		if(this.tableu[pile].isEmpty() && card.getRank() != 13) return false;
		if(!this.tableu[pile].isEmpty() &&
			((Card) this.tableu[pile].peek()).getRank() - card.getRank() != 1) return false;
		this.tableu[pile].push(card);
		return true;
	}

	/**
	* Gets one card from a chosen foundation. Returns null if chosen foundation is
	* empty.
	* @param suit Chosen foundation.
	* @return Card taken from said foundation.
	*/
	public Card getFromFoundation(Suit suit) {
		int s = 0;
		for(;s<4;s++) {
			if(Constant.SUITS[s] == suit) break;
		}
		if(this.foundations[s].isEmpty()) return null;
		return (Card) this.foundations[s].pop();
	}

	/**
	* Gets a user-determined amount of cards from a chosen tableu. Returns null
	* if chosen pile is empty. As with the rules of solitaire, only cards faced-up
	* are chosen, and if more than the allowed or possible amount of cards is
	* requested, then the maximum amount of cards allowed to be taken is taken.
	* @param pile Tableu pile of choice.
	* @param numberOfCards Number of cards to be taken from the pile.
	* @return Stack of cards taken from the pile, in reverse order.
	*/
	public LinkedStack getFromTableu(int pile, int numberOfCards) {
		if(this.tableu[pile].isEmpty()) return null;
		LinkedStack output = new LinkedStack();
		for(; numberOfCards > 0; numberOfCards--) {
			if(this.tableu[pile].peek() == null) break;
			if(!((Card) this.tableu[pile].peek()).getFaceUp()) break;
			output.push(this.tableu[pile].pop());
			if(this.tableu[pile].isEmpty()) break;
		}
		if(!this.tableu[pile].isEmpty()) this.faceCard((Card) this.tableu[pile].peek(), true);
		return output;
	}

	/**
	* Gets one card from the talon.
	* @return Card drawn from the talon.
	*/
	public Card getFromTalon() {
		return (Card) this.talon.pop();
	}

	/**
	* Saves the game state into the chosen filename.
	*	@param filename Filename / directory of the save file.
	* @return Whether or not the file saving was successful.
	*/
	public boolean saveGame(String filename) {
		filename.trim();
		try {
			File f = new File(filename);
			f.createNewFile();
			FileWriter file = new FileWriter(f);
			file.write(this.stock.toRawString());
			file.write("0\n" + this.talon.toRawString());
			for(LinkedStack x : this.foundations){
				file.write("0\n" + x.toRawString());
			}
			for(LinkedStack x : this.tableu){
				file.write("0\n" + x.toRawString());
			}
			file.write("0\n");
			file.flush();
			file.close();
		} catch(Exception e) {
			return false;
		}
		return true;
	}

	/**
	* Loads a game from a save file.
	* @param filename Filename / directory of the save file.
	* @return Whether or not the game loading was successful.
	*/
	public boolean loadGame(String filename) {
		filename.trim();
		try {
			File f = new File(filename);
			FileReader file = new FileReader(f);
			String fileInput = "";
			char c;
			int x = 0;
			while((c = (char) file.read()) != (char) -1) { fileInput += "" + c; }
			String[] tokens = fileInput.split("\n");

			// Stock
			this.stock.clear();
			for(; x<tokens.length; x++) {
				if(tokens[x].equals("000")) x++;
				if(tokens[x].equals("0")) break;
				this.stock.push(new Card(tokens[x]));
			}
			this.stock.reverse();
			x++;

			// Talon
			this.talon.clear();
			for(; x<tokens.length; x++) {
				if(tokens[x].equals("000")) x++;
				if(tokens[x].equals("0")) break;
				this.talon.push(new Card(tokens[x]));
			}
			this.talon.reverse();
			x++;

			// Foundations
			for(LinkedStack ls : this.foundations) {
				ls.clear();
				for(; x<tokens.length; x++) {
					if(tokens[x].equals("000")) x++;
					if(tokens[x].equals("0")) break;
					ls.push(new Card(tokens[x]));
				}
				ls.reverse();
				x++;
			}

			// Tableus
			for(LinkedStack ls : this.tableu) {
				ls.clear();
				for(; x<tokens.length; x++) {
					if(tokens[x].equals("000")) x++;
					if(tokens[x].equals("0")) break;
					ls.push(new Card(tokens[x]));
				}
				ls.reverse();
				x++;
			}

			file.close();
		} catch(Exception e) {
			return false;
		}
		return true;
	}
}

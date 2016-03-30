package me1.delacruz;

/**
* <h1>Constant</h1>
* The Constant class stores a list of String and other constants used in the
* project. Some constants stores here include graphical characters and suits.
*
* @author	Francis Zac dela Cruz
* @since	2015-03-26
*/

public class Constant {
	// Array of Suits and their corresponding Unicode symbols
	static final Suit[] SUITS = {Suit.SPADES, Suit.HEARTS, Suit.DIAMONDS, Suit.CLUBS};
	static final String SPDS = new String(Character.toChars('\u2660'));
	static final String HRTS = new String(Character.toChars('\u2661'));
	static final String DMND = new String(Character.toChars('\u2662'));
	static final String CLBS = new String(Character.toChars('\u2663'));

	// Set of Box Unicode symbols
	static final String BOXNW = new String(Character.toChars('\u250C'));
	static final String BOXNE = new String(Character.toChars('\u2510'));
	static final String BOXSW = new String(Character.toChars('\u2514'));
	static final String BOXSE = new String(Character.toChars('\u2518'));
	static final String BOXNS = new String(Character.toChars('\u2500'));
	static final String BOXEW = new String(Character.toChars('\u2502'));

	// Set of Card templates
	static final String CARDTOP =
		BOXNW + BOXNS + BOXNS + BOXNS + BOXNS + BOXNS + BOXNE;
	static final String CARDTEXT =
		BOXEW + "%s  " + BOXEW;
	static final String CARDBODY =
		BOXEW + "     " + BOXEW;
	static final String CARDBOTTOM =
		BOXSW + BOXNS + BOXNS + BOXNS + BOXNS + BOXNS + BOXSE;
	static final String CARDTOPTMPL =
		BOXNW + BOXNS + "%s" + BOXNS + BOXNE;
	static final String CARDWIDTH = "       ";
	static final String CARDMARGIN = "   %s   ";

	// Templates for the Stock-Talon-Foundations part of the interface
	static final String STFTOP =
		CARDTOP + CARDTOP + CARDWIDTH + CARDTOP + CARDTOP + CARDTOP + CARDTOP;
	static final String STFBODY =
		CARDBODY + CARDBODY + CARDWIDTH + CARDBODY + CARDBODY + CARDBODY + CARDBODY;
	static final String STFBOTTOM =
		CARDBOTTOM + CARDBOTTOM + CARDWIDTH + CARDBOTTOM + CARDBOTTOM + CARDBOTTOM + CARDBOTTOM;

	// Error messages and templates
	static final String TEMPLATE = "###\n%s\n###\n\n";
	static final String ERRORS[] = {"", "Invalid input.",
								"Cannot draw / move cards or manage game states with other cards in your hand.",
								"Cannot move certain cards to foundation. Try again.",
								"Cannot move certain cards to tableu. Try again.",
								"Cannot draw from empty piles. Try again.",
								"Out of redeals. Reset the game or find another move.",
								"File error. Maybe the file doesn't exist. Try again.",
								"Only one card at a time can be moved to the foundation. Try again.",
								"Chosen pile is out of bounds. Try again."};
}

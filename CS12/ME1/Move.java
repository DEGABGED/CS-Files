package me1.delacruz;

public class Move {
	/*
		-1: Empty / Invalid
		0: Stock
		1: Talon
		2: Hand
		3-6: Foundations
		7-13: Tableus
		Note: To denote a top card flip, both src and dest piles would be equal,
			and the cardsMoved will be 1 or 0 depending on whether the card was
			flipped up or down.
		Move index indicates groups of moves (eg. a chain of moves which move cards
			between tableus will be under 1 index)
	*/
	private int srcPile;
	private int destPile;
	private int cardsMoved;
	private int moveIndex;

	public Move(int src, int dest, int count, int ndx) {
		this.srcPile = src;
		this.destPile = dest;
		this.cardsMoved = count;
		this.moveIndex = ndx;
	}

	public int getSrc() { return this.srcPile; }
	public int getDest() { return this.destPile; }
	public int getCount() { return this.cardsMoved; }
	public int getIndex() { return this.moveIndex; }

	public String toString() {
		return "<"+this.srcPile+","+this.destPile+","+this.cardsMoved+">";
	}
}

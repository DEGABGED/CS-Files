package me1.delacruz;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;

public class GUITemplate extends Canvas implements MouseListener {
	private BufferedImage img;
	private int width = 600;
	private int height = 610;
	private int cardWidth = 70;
	private int cardHeight = 95;
	private int cardMarginX = 10;
	private int cardMarginY = 20;
	private int cardSliver = 20;
	private int marginX = 20;
	private int marginY = 25;

	private Solitaire game;
	private LinkedStack stockPrint;
	private LinkedStack talonPrint;
	private LinkedStack[] foundationsPrint;
	private LinkedStack[] tableusPrint;

	public GUITemplate() {
		setSize(width, height);
		this.addMouseListener(this);
	}

	public GUITemplate(Solitaire game) {
		setSize(width, height);
		this.game = game;
		this.addMouseListener(this);
	}

	private int row2PositionsX(int x) { return marginX+(cardMarginX+cardWidth)*x; }
	private int row2PositionsY(int y) { return marginY+cardHeight+cardMarginY+(y*cardSliver); }

	// The printGameState function in SGUIO will parse the card piles and pass them here
	public void paint(Graphics ga) {
		int x = 0, y = 0;
		Graphics2D g = (Graphics2D) ga;
		g.setColor(new Color(0x00bb44)); //greeeen
		g.fillRect(0, 0, width, height);

		g.setColor(Color.BLACK);
		// Draw the empty piles first
		/*
		for(x = 0; x < 7; x++) {
			if(x != 2) g.drawRect(marginX+(cardMarginX+cardWidth)*x, marginY, cardWidth, cardHeight);
			g.drawRect(marginX+(cardMarginX+cardWidth)*x, marginY+cardHeight+cardMarginY+(y*cardSliver), cardWidth, cardHeight);
		}
		*/

		// Get the list of cards to print, and in what order
		stockPrint = game.getStock();
		talonPrint = game.getTalon();
		foundationsPrint = new LinkedStack[4];
		for(int c = 0; c < 4; c++) {
			foundationsPrint[c] = game.getFoundations()[c].getReverse();
		}
		tableusPrint = new LinkedStack[7];
		for(int c = 0; c < 7; c++) {
			tableusPrint[c] = game.getTableus()[c].getReverse();
		}

		//Print the stock and talon
		if(stockPrint!=null && !stockPrint.isEmpty()) {
			g.drawImage(getCardImage((Card) stockPrint.peek())
			, marginX, marginY, cardWidth, cardHeight, null);
		} else {
			g.drawRect(marginX, marginY, cardWidth, cardHeight);
		}

		if(talonPrint!=null && !talonPrint.isEmpty()) {
			g.drawImage(getCardImage((Card) talonPrint.peek())
			, marginX+cardMarginX+cardWidth, marginY, cardWidth, cardHeight, null);
		} else {
			g.drawRect(marginX+(cardMarginX+cardWidth), marginY, cardWidth, cardHeight);
		}

		//Print the foundations
		for(int c = 0; c<4; c++) {
			if(foundationsPrint[c]!=null && !foundationsPrint[c].isEmpty()) {
				g.drawImage(getCardImage((Card) foundationsPrint[c].peek())
				, marginX+(cardMarginX+cardWidth)*(c+3), marginY, cardWidth, cardHeight, null);
			} else {
				g.drawRect(marginX+(cardMarginX+cardWidth)*(c+3), marginY, cardWidth, cardHeight);
			}
		}

		//Print the tableus
		int t = 0;
		for(int c = 0; c<7; c++) {
			t=0;
			if(tableusPrint[c]!=null) {
				while(!tableusPrint[c].isEmpty()) {
					g.drawImage(getCardImage((Card) tableusPrint[c].pop())
					, marginX+(cardMarginX+cardWidth)*c, marginY+cardHeight+cardMarginY+(t*cardSliver), cardWidth, cardHeight, null);
					t++;
				}
			} else {
				g.drawRect(marginX+(cardMarginX+cardWidth)*c, marginY+cardHeight+cardMarginY+(y*cardSliver), cardWidth, cardHeight);
			}
		}
	}

	public void mouseEntered(MouseEvent e) {

	}

	public void mouseExited(MouseEvent e) {

	}

	public void mouseClicked(MouseEvent e) {
		int x = e.getX(), y = e.getY();
		System.out.println("" + x + " and " + y);
		int[] dmp = getChosenPile(x,y); // A y value of 0 means 'top of the pile'
		System.out.println("" + dmp[0] + " and " + dmp[1]);
		processInput(dmp[0], dmp[1]);
	}

	private void processInput(int pile, int cardPos) {

	}

	private int[] getChosenPile(int x, int y) { //returns a 2 int array; 1st one indicates the pile, 2nd one indicates the card index
		int[] output = {2,0}; // The empty pile between the talon and foundations
		x -= cardMarginX;
		output[0] = x / (cardWidth+cardMarginX);
		if (y > marginY && y < marginY+cardHeight) {
			System.out.println("StockTalon");
			output[1] = 0;
			if (output[0] == 7) output[0] = -1;
		} else if (y > marginY+cardHeight+cardMarginY && y < height-marginY) {
			System.out.println("Tableus");
			output[0] += 7;
			y -= (marginY+cardMarginY+cardHeight);
			if(output[0] >= 7 && output[0] < 14) {
				output[1] = this.game.getTableus()[output[0] - 7].getSize() - (y / cardSliver) - 1;
			}
			if(output[1] < 0 && output[1] > -5) output[1] = 0;
		} else {
			System.out.println("Border");
		}
		return output;
	}

	public void mousePressed(MouseEvent e) {

	}

	public void mouseReleased(MouseEvent e) {

	}

	public static String getCardImageName(Card c) {
		if(! c.getFaceUp()) return "./imagedeck/155.png";
		int cardnum = 0;
		switch(c.getSuit()) {
			case DIAMONDS: cardnum = 0; break;
			case CLUBS: cardnum = 13; break;
			case HEARTS: cardnum = 26; break;
			case SPADES: cardnum = 39; break;
		}
		cardnum += c.getRank();
		return "./imagedeck/1" + (cardnum < 10 ? ("0" + cardnum) : cardnum) + ".png";
	}

	// Ask sir if we can use his code for image reading
	public BufferedImage getCardImage(Card c) {
		String filename = "";
		if(! c.getFaceUp()){ filename = "./imagedeck/155.png";}
		else {
		int cardnum = 0;
		switch(c.getSuit()) {
			case DIAMONDS: cardnum = 0; break;
			case CLUBS: cardnum = 13; break;
			case HEARTS: cardnum = 26; break;
			case SPADES: cardnum = 39; break;
		}
		cardnum += c.getRank();
		filename = "./imagedeck/1" + (cardnum < 10 ? ("0" + cardnum) : cardnum) + ".png";
		}
		try {
			return ImageIO.read(new File(filename));
		} catch (Exception e) {
			System.out.println("error; filename: " + filename);
			e.printStackTrace();
			return null;
		}
	}
}

package me1.delacruz;

import java.awt.*;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class GUITemplate extends JPanel {
	private BufferedImage img;
	private static int width = 600;
	private static int height = 610;
	private static int cardWidth = 70;
	private static int cardHeight = 95;
	private static int cardMarginX = 10;
	private static int cardMarginY = 20;
	private static int cardSliver = 20;
	private static int marginX = 20;
	private static int marginY = 25;

	private Solitaire game;
	private Deck stockPrint;
	private Deck talonPrint;
	private Deck[] foundationsPrint;
	private Deck[] tableusPrint;
	private int clickedPile;
	
	public GUITemplate(Solitaire game, MouseListener listener) {
		setPreferredSize(new Dimension(width, height));
		this.game = game;
		this.addMouseListener(listener);
		this.clickedPile = -1; // A pile has not yet been clicked
	}

	private int row2PositionsX(int x) { return marginX+(cardMarginX+cardWidth)*x; }
	private int row2PositionsY(int y) { return marginY+cardHeight+cardMarginY+(y*cardSliver); }

	/**
	 * This method sets the game object and clicked pile, then repaints the
	 * JPanel.
	 * @param game The game object.
	 * @param clickedPile The clicked pile; for drawing the pile indicator.
	 */
	public void updateView(Solitaire game, int clickedPile) {
		// Set the clicked pile and game
		this.game = game;
		this.clickedPile = clickedPile;

		this.repaint();
	}

	public boolean setPiles() {
		// Get the list of cards to print, and in what order
		stockPrint = game.getStock();
		talonPrint = game.getTalon();
		foundationsPrint = new Deck[4];
		for(int c = 0; c < 4; c++) {
			foundationsPrint[c] = game.getFoundations()[c];
		}
		tableusPrint = new Deck[7];
		for(int c = 0; c < 7; c++) {
			tableusPrint[c] = game.getTableus()[c].getReverse();
		}
		return true;
	}

	// The printGameState function in SGUIO will parse the card piles and pass them here
	public void paintComponent(Graphics ga) {
		int x = 0, y = 0;
		Graphics2D g = (Graphics2D) ga;
		g.setColor(new Color(0x00bb44)); //greeeen
		g.fillRect(0, 0, width, height);
		g.setColor(Color.BLACK);

		this.setPiles();

		//Print the stock and talon
		if(stockPrint!=null && !stockPrint.isEmpty()) {
			g.drawImage(getCardImage(stockPrint.peek())
			, marginX, marginY, cardWidth, cardHeight, null);
		} else {
			g.drawRect(marginX, marginY, cardWidth, cardHeight);
		}

		int cmxcw = cardMarginX + cardWidth;
		if(talonPrint!=null && !talonPrint.isEmpty()) {
			g.drawImage(getCardImage(talonPrint.peek())
			, marginX+cmxcw, marginY, cardWidth, cardHeight, null);
		} else {
			g.drawRect(marginX+(cmxcw), marginY, cardWidth, cardHeight);
		}

		//Print the foundations
		for(int c = 0; c<4; c++) {
			if(foundationsPrint[c]!=null && !foundationsPrint[c].isEmpty()) {
				g.drawImage(getCardImage(foundationsPrint[c].peek())
				, marginX+(cmxcw)*(c+3), marginY, cardWidth, cardHeight, null);
			} else {
				g.drawRect(marginX+(cmxcw)*(c+3), marginY, cardWidth, cardHeight);
			}
		}

		//Print the tableus
		int mychcmy = marginY+cardHeight+cardMarginY;
		int t = 0;
		for(int c = 0; c<7; c++) {
			t=0;
			if(tableusPrint[c]!=null) {
				while(!tableusPrint[c].isEmpty()) {
					g.drawImage(getCardImage(tableusPrint[c].pop())
					, marginX+(cmxcw)*c, mychcmy+(t*cardSliver), cardWidth, cardHeight, null);
					t++;
				}
			} else {
				g.drawRect(marginX+(cmxcw)*c, mychcmy+(y*cardSliver), cardWidth, cardHeight);
			}
		}

		//Print the pile indicator
		if (this.clickedPile >= 0 && this.clickedPile < 7 && this.clickedPile != 2) {
			// Point up
			int triBaseX = marginX + (cardWidth + cardMarginX)*(clickedPile) + 30;
			int triBaseY = marginY + cardHeight + 11;
			int xarr[] = {triBaseX, triBaseX+5, triBaseX+10};
			int yarr[] = {triBaseY, triBaseY-10, triBaseY};
			g.fillPolygon(xarr, yarr, 3);
		} else if (this.clickedPile >= 7 && this.clickedPile < 14) {
			// Point down
			int triBaseX = marginX + (cardWidth + cardMarginX)*(clickedPile - 7) + 30;
			int triBaseY = marginY + cardHeight + 1;
			int xarr[] = {triBaseX, triBaseX+5, triBaseX+10};
			int yarr[] = {triBaseY, triBaseY+10, triBaseY};
			g.fillPolygon(xarr, yarr, 3);
		}
	}

	public static int[] getChosenPile(int x, int y) { //returns a 2 int array; 1st one indicates the pile, 2nd one indicates the card index
		int[] output = {-1,0}; // The empty pile between the talon and foundations
		x -= cardMarginX;
		output[0] = x / (cardWidth+cardMarginX);
		if (y > marginY && y < marginY+cardHeight) {
			System.out.println("StockTalon");
			output[1] = 0;
			if (output[0] == 7 || output[0] == 2) output[0] = -1;
		} else if (y > marginY+cardHeight+cardMarginY && y < height-marginY) {
			System.out.println("Tableus");
			output[0] += 7;
			y -= (marginY+cardMarginY+cardHeight);
			/* Code changed because of problems with static references
			if(output[0] >= 7 && output[0] < 14) {
				output[1] = tableusPrint[output[0] - 7].getSize() - (y / cardSliver) - 1;
			}
			*/
			if(output[0] >= 7 && output[0] < 14) {
				output[1] = (y / cardSliver);
			} else {
				output[0] = -1;
			}
		} else {
			System.out.println("Border");
			output[0] = -1;
		}
		return output;
	}

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

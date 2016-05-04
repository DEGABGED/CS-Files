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
	}

	public GUITemplate(Solitaire game) {
		setSize(width, height);
		this.game = game;
	}

	private int row2PositionsX(int x) { return marginX+(cardMarginX+cardWidth)*x; }
	private int row2PositionsY(int y) { return marginY+cardHeight+cardMarginY+(y*cardSliver); }

	// The printGameState function in SGUIO will parse the card piles and pass them here
	public void paint(Graphics ga) {
		int x = 0, y = 0;
		Graphics2D g = (Graphics2D) ga;
		g.setColor(new Color(0xfffdd0));
		g.fillRect(0, 0, width, height);

		g.setColor(Color.BLACK);
		// Test to draw the original template
		for(x = 0; x < 7; x++) {
			if(x != 2) g.drawRect(marginX+(cardMarginX+cardWidth)*x, marginY, cardWidth, cardHeight);
			/*
			for(y = 0; y < x; y++) {
				g.drawRect(marginX+(cardMarginX+cardWidth)*x, marginY+cardHeight+cardMarginY+(y*cardSliver), cardWidth, cardSliver);
			}*/
			g.drawRect(marginX+(cardMarginX+cardWidth)*x, marginY+cardHeight+cardMarginY+(y*cardSliver), cardWidth, cardHeight);
		}

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
		//System.out.println("Someof");
		if(stockPrint!=null && !stockPrint.isEmpty()) {
			//System.out.println("Stock: " + stockPrint);
			g.drawImage(getCardImage((Card) stockPrint.peek())
			, marginX, marginY, cardWidth, cardHeight, null);
		}
		if(talonPrint!=null && !talonPrint.isEmpty()) {
			//System.out.println("Talon: " + talonPrint);
			g.drawImage(getCardImage((Card) talonPrint.peek())
			, marginX+cardMarginX+cardWidth, marginY, cardWidth, cardHeight, null);
		}

		//Print the foundations
		for(int c = 0; c<4; c++) {
			if(foundationsPrint[c]!=null && !foundationsPrint[c].isEmpty()) {
				g.drawImage(getCardImage((Card) foundationsPrint[c].peek())
				, marginX+(cardMarginX+cardWidth)*(c+3), marginY, cardWidth, cardHeight, null);
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
			}
		}
	}

	public void mouseEntered(MouseEvent e) {

	}

	public void mouseExited(MouseEvent e) {

	}

	public void mouseClicked(MouseEvent e) {

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

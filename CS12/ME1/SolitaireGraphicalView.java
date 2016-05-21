package me1.delacruz;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

/**
* <h1>SolitaireGraphicalView</h1>
* The SolitaireGraphicalView class, which implements the
* SolitaireView interface, handles the GUI of the application. It also contains
* constants regarding the coordinates and dimensions of images and margins, as
* well as a static method that converts raw X and Y mouse coordinates into the
* pile and card index located in those coordinates.
*
* @author	Francis Zac dela Cruz
* @since	2015-05-18
*/
public class SolitaireGraphicalView extends JPanel implements SolitaireView {
	private BufferedImage img;
	private static final int width = 600;
	private static final int height = 610;
	private static final int cardWidth = 70;
	private static final int cardHeight = 95;
	private static final int cardMarginX = 10;
	private static final int cardMarginY = 20;
	private static final int cardSliver = 20;
	private static final int marginX = 20;
	private static final int marginY = 25;

	private JFrame frame;
	private JPanel statusBar;
	private JLabel status;
	private JMenuBar menuBar;

	private JMenu options;
	private JMenuItem newgame;
	private JMenuItem savegame;
	private JMenuItem loadgame;
	private JMenuItem exitgame;
	private JMenu gameactions;
	private JMenuItem undo;
	private JMenuItem redeal;

	private Solitaire game;
	private Deck stockPrint;
	private Deck talonPrint;
	private Deck[] foundationsPrint;
	private Deck[] tableusPrint;
	private int clickedPile;
	
	/**
	 * This constructor sets the Solitaire game and the MouseListener object.
	 * It also sets the size of the panel.
	 * @param game The game object.
	 * @param listener The mouse listener object.
	 */
	public SolitaireGraphicalView(Solitaire game, MouseActionListener listener) {
		// For the game itself
		setPreferredSize(new Dimension(width, height));
		this.game = game;
		this.addMouseListener(listener);
		this.clickedPile = -1; // A pile has not yet been clicked

		// For the frame and template / view
		frame = new JFrame();
		frame.setLayout(new BorderLayout());
		frame.setTitle("Solitaire (Klondlike)");

		// For the status bar
		statusBar = new JPanel();
		frame.add(statusBar, BorderLayout.SOUTH);
		statusBar.setPreferredSize(new Dimension(frame.getWidth(), 25));
		statusBar.setBackground(new Color(0x40eb74));
		statusBar.setLayout(new BoxLayout(statusBar, BoxLayout.X_AXIS));
		status = new JLabel("  Welcome!");
		status.setHorizontalAlignment(SwingConstants.LEFT);
		statusBar.add(status);

		// For the menu bar
		menuBar = new JMenuBar();
		options = new JMenu("Options");
		newgame = new JMenuItem("New Game");
		newgame.setActionCommand("New");
		newgame.addActionListener(listener);
		savegame = new JMenuItem("Save Game");
		savegame.setActionCommand("Save");
		savegame.addActionListener(listener);
		loadgame = new JMenuItem("Load Game");
		loadgame.setActionCommand("Load");
		loadgame.addActionListener(listener);
		exitgame = new JMenuItem("Exit");
		exitgame.setActionCommand("Exit");
		exitgame.addActionListener(listener);
		gameactions = new JMenu("Game Actions");
		undo = new JMenuItem("Undo");
		undo.setActionCommand("Undo");
		undo.addActionListener(listener);
		redeal = new JMenuItem("Redeal");
		redeal.setActionCommand("Redeal");
		redeal.addActionListener(listener);

		options.add(newgame);
		options.add(savegame);
		options.add(loadgame);
		options.add(exitgame);
		gameactions.add(undo);
		gameactions.add(redeal);
		menuBar.add(options);
		menuBar.add(gameactions);
		frame.setJMenuBar(menuBar);

		frame.setResizable(false);
		frame.add(this, BorderLayout.CENTER);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.setResizable(false);
	}

	/**
	 * Computes the X coordinate of a tableu pile base's top left corner, given
	 * which tableu it is.
	 * @param x Index of tableu. First tableu is of index 0.
	 * @return The X coordinate of the tableu's top left corner.
	 */
	private int row2PositionsX(int x) { return marginX+(cardMarginX+cardWidth)*x; }

	/**
	 * Computes the Y coordinate of a tableu pile base's top left corner, given
	 * which tableu it is.
	 * @param y Index of tableu. First tableu is of index 0.
	 * @return The Y coordinate of the tableu's top left corner.
	 */
	private int row2PositionsY(int y) { return marginY+cardHeight+cardMarginY+(y*cardSliver); }

	/**
	 * This method sets the game object and clicked pile, then repaints the
	 * JPanel.
	 * @param game The game object.
	 * @param args The clicked pile; for drawing the pile indicator.
	 */
	public void updateView(Solitaire game, int[] args) {
		// Set the clicked pile and game
		if (args.length != 5) return;
		this.game = game;
		this.clickedPile = args[0];

		if (args[1] == 1) {
			status.setText(" YOU WIN! ");
		} else {
			String statusLabel = "  Status: ";
			statusLabel += "Redeals > " + args[2];
			statusLabel += ", Stock left > " + args[3];
			statusLabel += ", Moves > " + args[4];
			status.setText(statusLabel);
		}

		this.repaint();
	}

	/**
	 * Sets the card piles to be printed, in the proper order (reverse for
	 * tableus, normal for everything else.)
	 */
	public void setPiles() {
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
	}

	/**
	 * Paints the JPanel with the proper colors and imagery.
	 * @param ga The graphics object of the JPanel.
	 */
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

	/**
	 * Gets the chosen pile and card index clicked given the raw x and y
	 * coordinates. Since computations are dependent on graphics values and
	 * dimensions, the method is written here, but made static.
	 * @param x X coordinate of the click.
	 * @param y Y coordinate of the click.
	 * @return 2 integer array; 1st one indicating the pile, 2nd one indicating
	 * the card index.
	 */
	public static int[] getChosenPile(int x, int y) {
		int[] output = {-1,0};
		x -= cardMarginX;
		output[0] = x / (cardWidth+cardMarginX);
		if (y > marginY && y < marginY+cardHeight) {
			output[1] = 0;
			if (output[0] == 7 || output[0] == 2) output[0] = -1;
		} else if (y > marginY+cardHeight+cardMarginY && y < height-marginY) {
			output[0] += 7;
			y -= (marginY+cardMarginY+cardHeight);
			if(output[0] >= 7 && output[0] < 14) {
				output[1] = (y / cardSliver);
			} else {
				output[0] = -1;
			}
		} else {
			output[0] = -1;
		}
		return output;
	}

	/**
	 * Gets the corresponding image of the card, given the card itself.
	 * @param c The card in question.
	 * @return The image of the card, for painting.
	 */
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
			System.out.println("Error; filename: " + filename);
			e.printStackTrace();
			return null;
		}
	}
}

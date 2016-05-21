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
		setPreferredSize(new Dimension(Constant.WIDTH, Constant.HEIGHT));
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
	private int row2PositionsX(int x) { return Constant.MARGINX+(Constant.CARDMARGINX+Constant.GCARDWIDTH)*x; }

	/**
	 * Computes the Y coordinate of a tableu pile base's top left corner, given
	 * which tableu it is.
	 * @param y Index of tableu. First tableu is of index 0.
	 * @return The Y coordinate of the tableu's top left corner.
	 */
	private int row2PositionsY(int y) { return Constant.MARGINY+Constant.GCARDHEIGHT+Constant.CARDMARGINY+(y*Constant.CARDSLIVER); }

	/**
	 * This method sets the game object and clicked pile, then repaints the
	 * JPanel.
	 * @param game The game object.
	 * @param args A 5-integer array containing the clicked pile, the win
	 * condition, the redeals left, the stock pile size, and the number of
	 * moves performed.
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
		g.fillRect(0, 0, Constant.WIDTH, Constant.HEIGHT);
		g.setColor(Color.BLACK);

		this.setPiles();

		//Print the stock and talon
		if(stockPrint!=null && !stockPrint.isEmpty()) {
			g.drawImage(getCardImage(stockPrint.peek())
			, Constant.MARGINX, Constant.MARGINY, Constant.GCARDWIDTH, Constant.GCARDHEIGHT, null);
		} else {
			g.drawRect(Constant.MARGINX, Constant.MARGINY, Constant.GCARDWIDTH, Constant.GCARDHEIGHT);
		}

		int cmxcw = Constant.CARDMARGINX + Constant.GCARDWIDTH;
		if(talonPrint!=null && !talonPrint.isEmpty()) {
			g.drawImage(getCardImage(talonPrint.peek())
			, Constant.MARGINX+cmxcw, Constant.MARGINY, Constant.GCARDWIDTH, Constant.GCARDHEIGHT, null);
		} else {
			g.drawRect(Constant.MARGINX+(cmxcw), Constant.MARGINY, Constant.GCARDWIDTH, Constant.GCARDHEIGHT);
		}

		//Print the foundations
		for(int c = 0; c<4; c++) {
			if(foundationsPrint[c]!=null && !foundationsPrint[c].isEmpty()) {
				g.drawImage(getCardImage(foundationsPrint[c].peek())
				, Constant.MARGINX+(cmxcw)*(c+3), Constant.MARGINY, Constant.GCARDWIDTH, Constant.GCARDHEIGHT, null);
			} else {
				g.drawRect(Constant.MARGINX+(cmxcw)*(c+3), Constant.MARGINY, Constant.GCARDWIDTH, Constant.GCARDHEIGHT);
			}
		}

		//Print the tableus
		int mychcmy = Constant.MARGINY+Constant.GCARDHEIGHT+Constant.CARDMARGINY;
		int t = 0;
		for(int c = 0; c<7; c++) {
			t=0;
			if(tableusPrint[c]!=null) {
				while(!tableusPrint[c].isEmpty()) {
					g.drawImage(getCardImage(tableusPrint[c].pop())
					, Constant.MARGINX+(cmxcw)*c, mychcmy+(t*Constant.CARDSLIVER), Constant.GCARDWIDTH, Constant.GCARDHEIGHT, null);
					t++;
				}
			} else {
				g.drawRect(Constant.MARGINX+(cmxcw)*c, mychcmy+(y*Constant.CARDSLIVER), Constant.GCARDWIDTH, Constant.GCARDHEIGHT);
			}
		}

		//Print the pile indicator
		if (this.clickedPile >= 0 && this.clickedPile < 7 && this.clickedPile != 2) {
			// Point up
			int triBaseX = Constant.MARGINX + (Constant.GCARDWIDTH + Constant.CARDMARGINX)*(clickedPile) + 30;
			int triBaseY = Constant.MARGINY + Constant.GCARDHEIGHT + 11;
			int xarr[] = {triBaseX, triBaseX+5, triBaseX+10};
			int yarr[] = {triBaseY, triBaseY-10, triBaseY};
			g.fillPolygon(xarr, yarr, 3);
		} else if (this.clickedPile >= 7 && this.clickedPile < 14) {
			// Point down
			int triBaseX = Constant.MARGINX + (Constant.GCARDWIDTH + Constant.CARDMARGINX)*(clickedPile - 7) + 30;
			int triBaseY = Constant.MARGINY + Constant.GCARDHEIGHT + 1;
			int xarr[] = {triBaseX, triBaseX+5, triBaseX+10};
			int yarr[] = {triBaseY, triBaseY+10, triBaseY};
			g.fillPolygon(xarr, yarr, 3);
		}
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

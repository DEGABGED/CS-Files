package me1.delacruz;

import javax.swing.*;
import javax.swing.event.MenuEvent;
import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;

public class SolitaireGraphicalIO implements SolitaireIO, MouseListener, ActionListener {
	private GUITemplate canvas;
	private JFrame frame;
	private JPanel statusBar;
	private JLabel status;
	private JMenuBar menuBar;

	private JMenu options;
	private JMenuItem newgame;
	private JMenuItem savegame;
	private JMenuItem loadgame;
	private JMenuItem exitgame;

	private SolitaireWrapper game;
	private LinkedStack move;
	private int clickedPile;

	public SolitaireGraphicalIO() {
		// For the game itself
		this.game = new SolitaireWrapper();
		this.move = new LinkedStack();
		this.clickedPile = -1;

		// For the frame and template / view
		frame = new JFrame();
		canvas = new GUITemplate(this.game, this);
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
		newgame.addActionListener(this);
		savegame = new JMenuItem("Save Game");
		savegame.setActionCommand("Save");
		savegame.addActionListener(this);
		loadgame = new JMenuItem("Load Game");
		loadgame.setActionCommand("Load");
		loadgame.addActionListener(this);
		exitgame = new JMenuItem("Exit");
		exitgame.setActionCommand("Exit");
		exitgame.addActionListener(this);

		options.add(newgame);
		options.add(savegame);
		options.add(loadgame);
		options.add(exitgame);
		menuBar.add(options);
		frame.setJMenuBar(menuBar);

		frame.add(canvas, BorderLayout.CENTER);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.setResizable(false);
	}

	public void actionPerformed(ActionEvent e) {
		String source = e.getActionCommand();
		switch(source) {
			case "New":
				this.game = new SolitaireWrapper();
				printGameState();
				break;
			case "Save":
				if (!this.game.saveGame(JOptionPane.showInputDialog("Enter filename/path:: "))) {
					JOptionPane.showMessageDialog(null, "Sorry, file IO error. Maybe the file path doesn't exist.", "File Error", JOptionPane.ERROR_MESSAGE);
				}
				break;
			case "Load":
				if(!this.game.loadGame(JOptionPane.showInputDialog("Enter filename/path:: "))) {
					JOptionPane.showMessageDialog(null, "Sorry, file IO error. Maybe the file path doesn't exist.", "File Error", JOptionPane.ERROR_MESSAGE);
				} else {
					printGameState();
				}
				break;
			case "Exit":
				frame.dispatchEvent(new WindowEvent(frame, WindowEvent.WINDOW_CLOSING));
				break;
		}
	}

	public void mouseEntered(MouseEvent e) {
	}

	public void mouseExited(MouseEvent e) {
	}

	public void mouseClicked(MouseEvent e) {
		getGameInput(e);
	}

	public void mousePressed(MouseEvent e) {
	}

	public void mouseReleased(MouseEvent e) {
	}

	public void printGameState() {
		// reprint game status
		String statusLabel = "  Status: ";
		statusLabel += "Redeals > " + this.game.getRedealsLeft();
		statusLabel += ", Stock left > " + this.game.getStock().getSize();
		status.setText(statusLabel);
		// repainting
		this.canvas.updateView(this.game, this.clickedPile);
	}

	public boolean getGameInput(Object o) {
		MouseEvent e = (MouseEvent) o;
		int x = e.getX(), y = e.getY();
		int[] cardPos = canvas.getChosenPile(x,y); // A y value of 0 means 'top of the pile'
		// Set the cardPos[1] for tableus such that the top card is card 0
		if(cardPos[0] >= 7 && cardPos[0] < 14) {
			cardPos[1] = game.getTableus()[cardPos[0] - 7].getSize() - cardPos[1] - 1;
		}
		if(cardPos[1] < 0 && cardPos[1] > -5) cardPos[1] = 0;

		System.out.println("" + cardPos[0] + " and " + cardPos[1]);
		if (cardPos[0] < 0 || cardPos[1] < 0) {
			move.clear();
			this.clickedPile = -1;
			printGameState();
			return false;
		}

		this.clickedPile = cardPos[0];
		// Prepare to move the cards
		boolean output = true;
		move.push(new Integer(cardPos[0]));
		move.push(new Integer(cardPos[1]));
		if (cardPos[0] == 0 || move.getSize() >= 4) {
			output = processGameInput();
			move.clear();
		}

		// Change the pointed pile
		// if(output) {
			printGameState();
		// }
		System.out.println(this.game.getMoves());
		System.out.println(this.game.getHand());
		return output;
	}

	private boolean processGameInput() {
			this.clickedPile = -1;
			if (move.getSize() == 2) {
				// Clicked pile is stock
				// Either move 1 from stock to talon
				// or move all from talon to stock
				if (this.game.getStock().isEmpty()) {
					this.game.redeal();
				} else {
					this.game.draw();
				}
			} else {
				int[] moves = new int[4];
				for(int i=3; i>=0; i--) moves[i] = ((Integer) move.pop()).intValue();
				System.out.println("Processing pile " + moves[0] + " cndx " + moves[1] + " -> pile " + moves[2] + " cndx " + moves[3]);
				moves[1]++; // convert card num index to card num
				if (moves[1] < 2) {
					// Single card
					if (!this.game.moveSingleCard(moves[0], moves[2])) return false;
				} else {
					// Multiple cards
					if (!this.game.moveMultipleCards(moves[0], moves[2], moves[1])) return false;
				}
			}
			return true;
	}
}

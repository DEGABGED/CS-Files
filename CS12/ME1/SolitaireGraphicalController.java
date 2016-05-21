package me1.delacruz;

import javax.swing.*;
import javax.swing.event.MenuEvent;
import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;

/**
* <h1>SolitaireGraphicalController</h1>
* The SolitaireGraphicalController class, which implements the
* SolitaireController interface, handles the flow of data between the Solitaire
* game object and the user interface (in this case, the GUI).
*
* @author	Francis Zac dela Cruz
* @since	2015-05-18
*/
public class SolitaireGraphicalController implements SolitaireController, MouseActionListener {
	private SolitaireView view;
	/*
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
	*/

	private SolitaireWrapper game;
	private LinkedStack<Integer> move;
	private int clickedPile;

	/**
	 * This constructor creates a new game object and move stack, and sets up
	 * the Java Swing GUI.
	 */
	public SolitaireGraphicalController() {
		// For the game itself
		this.game = new SolitaireWrapper();
		this.move = new LinkedStack<>();
		this.clickedPile = -1;

		/*
		// For the frame and template / view
		frame = new JFrame();
		canvas = new SolitaireGraphicalView(this.game, this);
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
		gameactions = new JMenu("Game Actions");
		undo = new JMenuItem("Undo");
		undo.setActionCommand("Undo");
		undo.addActionListener(this);
		redeal = new JMenuItem("Redeal");
		redeal.setActionCommand("Redeal");
		redeal.addActionListener(this);

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
		frame.add(canvas, BorderLayout.CENTER);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.setResizable(false);
		*/
		view = new SolitaireGraphicalView(this.game, this);
	}

	/**
	 * Listens for performed actions, particularly clicks in the menu buttons,
	 * and processes them.
	 */
	public void actionPerformed(ActionEvent e) {
		String source = e.getActionCommand();
		switch(source) {
			case "New":
				this.game = new SolitaireWrapper();
				this.move.clear();
				this.clickedPile = -1;
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
					this.move.clear();
					this.clickedPile = -1;
					printGameState();
				}
				break;
			case "Exit":
				//frame.dispatchEvent(new WindowEvent(frame, WindowEvent.WINDOW_CLOSING));
				System.exit(0);
				break;
			case "Undo":
				// Undo handler
				this.game.undoGroup();
				break;
			case "Redeal":
				if (this.game.redeal() < 0) {
					JOptionPane.showMessageDialog(null, "You're out of redeals!", "Move error", JOptionPane.ERROR_MESSAGE);
				}
				break;
		}
		printGameState();
	}

	/**
	 * Implemented from MouseListener.
	 * @param e Object which contains data on the mouse action.
	 */
	public void mouseEntered(MouseEvent e) {
	}

	/**
	 * Implemented from MouseListener.
	 * @param e Object which contains data on the mouse action.
	 */
	public void mouseExited(MouseEvent e) {
	}

	/**
	 * Listens for mouse clicks and passes the object containing mouse action
	 * data to the game input method.
	 * @param e Object which contains data on the mouse action.
	 */
	public void mouseClicked(MouseEvent e) {
		getGameInput(e);
	}

	/**
	 * Implemented from MouseListener.
	 * @param e Object which contains data on the mouse action.
	 */
	public void mousePressed(MouseEvent e) {
	}

	/**
	 * Implemented from MouseListener.
	 * @param e Object which contains data on the mouse action.
	 */
	public void mouseReleased(MouseEvent e) {
	}

	/**
	 * Prints the game state to the view. Also handles the status bar.
	 */
	public void printGameState() {
		// reprint game status
		/*
		if (this.game.isWin()) {
			status.setText(" YOU WIN! ");
		} else {
			String statusLabel = "  Status: ";
			statusLabel += "Redeals > " + this.game.getRedealsLeft();
			statusLabel += ", Stock left > " + this.game.getStock().getSize();
			statusLabel += ", Moves > " + this.game.getMoveCount();
			status.setText(statusLabel);
		}
		*/
		// repainting
		int[] args = {
			this.clickedPile,
			this.game.isWin() ? 1 : 0,
			this.game.getRedealsLeft(),
			this.game.getStock().getSize(),
			this.game.getMoveCount()
		};
		this.view.updateView(this.game, args);
	}

	/**
	 * Gets the game input, in this case the MouseEvent object, and prepares it
	 * into an array before having it processed.
	 * @param o Contains the mouse input data.
	 */
	public boolean getGameInput(Object o) {
		MouseEvent e = (MouseEvent) o;
		int x = e.getX(), y = e.getY();
		int[] cardPos = SolitaireGraphicalView.getChosenPile(x,y); // A y value of 0 means 'top of the pile'
		// Set the cardPos[1] for tableus such that the top card is card 0
		if(cardPos[0] >= 7 && cardPos[0] < 14) {
			cardPos[1] = game.getTableus()[cardPos[0] - 7].getSize() - cardPos[1] - 1;
		}
		if(cardPos[1] < 0 && cardPos[1] > -5) cardPos[1] = 0;

		if (cardPos[0] < 0 || cardPos[1] < 0) {
			move.clear();
			this.clickedPile = -1;
			printGameState();
			return false;
		}

		this.clickedPile = cardPos[0];
		// Prepare to move the cards
		int output = 1;
		move.push(new Integer(cardPos[0]));
		move.push(new Integer(cardPos[1]));
		if (cardPos[0] == 0 || move.getSize() >= 4) {
			// Build input array
			int[] input = new int[move.getSize()];
			for (int i=move.getSize()-1; i>=0; i--) input[i] = (move.pop()).intValue();
			output = processGameInput(input);
			move.clear();
		}

		printGameState();
		return output > 0;
	}

	/**
	 * Processes the game input.
	 * @param input Game input, in this case a 2 or 4 element array indicating
	 * the pile and card index clicked.
	 */
	public int processGameInput(int[] input) {
			this.clickedPile = -1;
			if (input.length == 2) {
				// Clicked pile is stock
				// Either move 1 from stock to talon
				// or move all from talon to stock
				if (this.game.getStock().isEmpty()) {
					this.game.redeal();
				} else {
					this.game.draw();
				}
			} else {
				if (input[0] == input[2] && input[0] >= 7 && input[0] < 14) return 0;
				input[1]++; // convert card num index to card num
				if (input[1] < 2) {
					// Single card
					if (!this.game.moveSingleCard(input[0], input[2])) return 0;
				} else {
					// Multiple cards
					if (!this.game.moveMultipleCards(input[0], input[2], input[1])) return 0;
				}
			}
			return 1;
	}
}

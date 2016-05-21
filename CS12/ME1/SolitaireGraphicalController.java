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
		int[] cardPos = getChosenPile(x,y); // A y value of 0 means 'top of the pile'
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
				if (input[0] == input[2] && input[0] > 0 && input[0] < 14) return 0;
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

	/**
	 * Gets the chosen pile and card index clicked given the raw x and y
	 * coordinates.
	 * @param x X coordinate of the click.
	 * @param y Y coordinate of the click.
	 * @return 2 integer array; 1st one indicating the pile, 2nd one indicating
	 * the card index.
	 */
	public int[] getChosenPile(int x, int y) {
		int[] output = {-1,0};
		x -= Constant.CARDMARGINX;
		output[0] = x / (Constant.GCARDWIDTH+Constant.CARDMARGINX);
		if (y > Constant.MARGINY && y < Constant.MARGINY+Constant.GCARDHEIGHT) {
			output[1] = 0;
			if (output[0] == 7 || output[0] == 2) output[0] = -1;
		} else if (y > Constant.MARGINY+Constant.GCARDHEIGHT+Constant.CARDMARGINY && y < Constant.HEIGHT-Constant.MARGINY) {
			output[0] += 7;
			y -= (Constant.MARGINY+Constant.CARDMARGINY+Constant.GCARDHEIGHT);
			if(output[0] >= 7 && output[0] < 14) {
				output[1] = (y / Constant.CARDSLIVER);
			} else {
				output[0] = -1;
			}
		} else {
			output[0] = -1;
		}
		return output;
	}
}

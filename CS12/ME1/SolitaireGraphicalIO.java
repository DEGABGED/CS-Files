package me1.delacruz;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;

public class SolitaireGraphicalIO extends JFrame implements SolitaireIO, MouseListener {
	public void printGameState() {
		// repainting
		this.canvas.repaint();
	}

	public boolean getGameInput(Object o) {
		MouseEvent e = (MouseEvent) o;
		int x = e.getX(), y = e.getY();
		System.out.println("" + x + " and " + y);
		int[] cardPos = canvas.getChosenPile(x,y); // A y value of 0 means 'top of the pile'
		// Set the cardPos[1] for tableus such that the top card is card 0
		if(cardPos[0] >= 7 && cardPos[0] < 14) {
			cardPos[1] = game.getTableus()[cardPos[0] - 7].getSize() - cardPos[1] - 1;
		}
		if(cardPos[1] < 0 && cardPos[1] > -5) cardPos[1] = 0;

		System.out.println("" + cardPos[0] + " and " + cardPos[1]);
		if (cardPos[0] < 0 || cardPos[1] < 0) {
			move.clear();
			return false;
		}

		// Prepare to move the cards
		boolean output = true;
		move.push(new Integer(cardPos[0]));
		move.push(new Integer(cardPos[1]));
		if (cardPos[0] == 0 || move.getSize() >= 4) {
			output = processGameInput();
		}
		System.out.println(move);

		if(output) {
			printGameState();
		}
		return output;
	}

	private boolean processGameInput() {
			if (move.getSize() == 2) {
				// Clicked pile is stock; means to move from stock to talon
				this.game.draw();
			} else {
				int[] moves = new int[4];
				for(int i=3; i>=0; i--) moves[i] = ((Integer) move.pop()).intValue();
				System.out.println("Processing " + Arrays.toString(moves));
				if (moves[0] >= 7 && moves[0] < 14) {
					// Src: tableu
					if (moves[2] >= 3 && moves[2] < 7) {
						// Dest: foundation
						hand = game.getFromTableu(moves[0] - 7, moves[1] + 1);
						if(hand == null) {
							move.clear();
							return false;
						}
						System.out.println("Hand: " + hand);
						if(!game.moveToFoundation((Card) hand.peek())){
							error = 3;
							// Move cards back to the tableu
							((Card) game.getTableus()[moves[0] - 7].peek()).setFaceUp(false);
							while(!hand.isEmpty()) {
								game.getTableus()[moves[0] - 7].push(hand.pop());
							}
							move.clear();
							return false;
						}
						hand.pop();
					}
				}
			}
			move.clear();
			return true;
	}

	private GUITemplate canvas;
	private JFrame frame;
	private JPanel statusBar;
	private JLabel status;
	private JMenu menuBar;

	private Solitaire game;
	private LinkedStack hand;
	private int error;
	private LinkedStack move;

	public SolitaireGraphicalIO() {
		// For the game itself
		this.game = new Solitaire();
		this.game.loadGame("outputres.sltr");
		this.hand = new LinkedStack();
		this.error = 0;
		this.move = new LinkedStack();

		// For the frame and template / view
		frame = new JFrame();
		canvas = new GUITemplate(this.game, this);

		frame.setLayout(new BorderLayout());
		statusBar = new JPanel();
		frame.add(statusBar, BorderLayout.SOUTH);
		statusBar.setPreferredSize(new Dimension(getWidth(), 25));
		statusBar.setBackground(new Color(0x40eb74));
		statusBar.setLayout(new BoxLayout(statusBar, BoxLayout.X_AXIS));

		status = new JLabel("  Status: ");
		status.setHorizontalAlignment(SwingConstants.LEFT);
		statusBar.add(status);

		//menuBar (soon)

		frame.add(canvas, BorderLayout.CENTER);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.setResizable(false);
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

	// To test the GUI; will be gotten rid of soon enough
	public static void main(String[] args) {
		SolitaireGraphicalIO io = new SolitaireGraphicalIO();
	}
}

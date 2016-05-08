package me1.delacruz;

import javax.swing.*;
import java.awt.*;

public class SolitaireGraphicalIO extends JFrame implements SolitaireIO {
	public void printGameState() {
		// repainting
	}

	public boolean getGameInput(Object o) {
		LinkedStack stack = (LinkedStack) o;
		int pile = ((Integer) stack.pop()).intValue();
		int cardPos = ((Integer) stack.pop()).intValue();
		System.out.println("Controller " + pile + " " + cardPos);
		return true;
	}

	private GUITemplate canvas;
	private JPanel statusBar;
	private JLabel status;
	private JMenu menuBar;

	private Solitaire game;
	private LinkedStack hand;
	private int error;

	public SolitaireGraphicalIO() {
		// For the game itself
		this.game = new Solitaire();
		this.game.loadGame("tableuseven.sltr");
		this.hand = new LinkedStack();
		this.error = 0;

		// For the template / view
		canvas = new GUITemplate(this.game, this);

		setLayout(new BorderLayout());
		statusBar = new JPanel();
		add(statusBar, BorderLayout.SOUTH);
		statusBar.setPreferredSize(new Dimension(getWidth(), 25));
		statusBar.setBackground(new Color(0x40eb74));
		statusBar.setLayout(new BoxLayout(statusBar, BoxLayout.X_AXIS));

		status = new JLabel("  Status: ");
		status.setHorizontalAlignment(SwingConstants.LEFT);
		statusBar.add(status);

		//menuBar

		add(canvas, BorderLayout.CENTER);
		pack();
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
		setResizable(false);
	}
	// To test the GUI; will be gotten rid of soon enough
	public static void main(String[] args) {
		SolitaireGraphicalIO frame = new SolitaireGraphicalIO();
		frame.printGameState();
	}
}

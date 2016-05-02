package me1.delacruz;

import javax.swing.*;
import java.awt.*;

public class SolitaireGraphicalIO extends JFrame implements SolitaireIO {
	public void printGameState() { return; }
	public boolean getGameInput() { return true; }

	private GUITemplate canvas;
	private JPanel statusBar;
	private JLabel status;

	public SolitaireGraphicalIO() {
		canvas = new GUITemplate();
		setLayout(new BorderLayout());

		statusBar = new JPanel();
		add(statusBar, BorderLayout.SOUTH);
		statusBar.setPreferredSize(new Dimension(getWidth(), 25));
		statusBar.setBackground(new Color(0xefedc0));
		statusBar.setLayout(new BoxLayout(statusBar, BoxLayout.X_AXIS));

		status = new JLabel("  Status: ");
		status.setHorizontalAlignment(SwingConstants.LEFT);
		statusBar.add(status);

		add(canvas, BorderLayout.CENTER);
		pack();
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
		setResizable(false);
	}

	public static void main(String[] args) {
		SolitaireGraphicalIO frame = new SolitaireGraphicalIO();
	}
}

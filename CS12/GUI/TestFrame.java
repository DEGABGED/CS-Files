// Java GUI libraries
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TestFrame extends JFrame implements ActionListener {
	JPanel panel;
	JButton b1, b2, b3, b4;
	JLabel label;
	ImageIcon image;

	public TestFrame() {
		// Create panel
		panel = new JPanel();
		panel.setLayout(new BorderLayout());

		// Create buttons
		b1 = new JButton("Button 1");
		b2 = new JButton("Button 2");
		b3 = new JButton("Button 3");
		b4 = new JButton("Button 4");

		// Add listeners
		b1.addActionListener(this);
		b2.addActionListener(this);
		b3.addActionListener(this);
		b4.addActionListener(this);

		// Create label
		label = new JLabel("M E M E S");
		label.setHorizontalAlignment(JLabel.CENTER);
		image = new ImageIcon("meme.jpg");
		label.setIcon(image);

		//Add components to panel
		panel.add(label, BorderLayout.PAGE_START);
		panel.add(b1, BorderLayout.CENTER);

		add(panel);
		pack();
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}

	public void actionPerformed(ActionEvent e) {
		String command = e.getActionCommand();
		JOptionPane.showMessageDialog(this, command);
	}

	/*
	public void keyPressed(KeyEvent e) {}
	public void keyReleased(KeyEvent e) {}
	public void keyTyped(KeyEvent e) {}
	*/

	public static void main(String[] args) {
		TestFrame tf = new TestFrame();
	}
}

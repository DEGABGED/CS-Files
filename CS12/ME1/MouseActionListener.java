package me1.delacruz;

import java.awt.event.*;

public interface MouseActionListener extends MouseListener, ActionListener {
	public void actionPerformed(ActionEvent e);
	public void mouseEntered(MouseEvent e);
	public void mouseExited(MouseEvent e);
	public void mouseClicked(MouseEvent e);
	public void mousePressed(MouseEvent e);
	public void mouseReleased(MouseEvent e);
}

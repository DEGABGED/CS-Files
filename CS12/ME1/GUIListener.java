package me1.delacruz;

import java.awt.event.*;
import javax.swing.event.*;

public interface GUIListener extends MouseListener, MenuListener {
		public void mouseEntered(MouseEvent e);

		public void mouseExited(MouseEvent e);

		public void mouseClicked(MouseEvent e);

		public void mousePressed(MouseEvent e);

		public void mouseReleased(MouseEvent e);

		public void menuCanceled(MenuEvent e);

		public void menuDeselected(MenuEvent e);

		public void menuSelected(MenuEvent e);
}

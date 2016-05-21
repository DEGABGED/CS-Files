package me1.delacruz;

import java.awt.event.*;

/**
* <h1>MouseActionListener</h1>
* The MouseActionListener interface combines the MouseListener and ActionListener
* interfaces. This interface is extended by the SolitaireGraphicalController
* class.
*
* @author	Francis Zac dela Cruz
* @since	2015-05-18
*/
public interface MouseActionListener extends MouseListener, ActionListener {
	/**
	 * Inherited from ActionListener.
	 */
	public void actionPerformed(ActionEvent e);

	/**
	 * Inherited from MouseListener.
	 */
	public void mouseEntered(MouseEvent e);

	/**
	 * Inherited from MouseListener.
	 */
	public void mouseExited(MouseEvent e);

	/**
	 * Inherited from MouseListener.
	 */
	public void mouseClicked(MouseEvent e);

	/**
	 * Inherited from MouseListener.
	 */
	public void mousePressed(MouseEvent e);

	/**
	 * Inherited from MouseListener.
	 */
	public void mouseReleased(MouseEvent e);
}

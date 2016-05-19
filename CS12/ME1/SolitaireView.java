package me1.delacruz;

/**
* <h1>SolitaireView</h1>
* The SolitaireView interface provides the updateView method, used for updating
* what the user sees.
*
* @author	Francis Zac dela Cruz
* @since	2015-05-18
*/
public interface SolitaireView {
	/**
	 * Updates the view, GUI or CLI.
	 * @param game The game object, used to access the various piles and
	 * other data.
	 * @param args A list of other miscellaneous arguments.
	 */
	public void updateView(Solitaire game, int[] args);
}

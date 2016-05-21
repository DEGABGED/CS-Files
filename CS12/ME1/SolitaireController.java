package mp1.delacruz;

/**
* <h1>SolitaireController</h1>
* The SolitaireController interface provides a list of methods which a
* SolitaireController would use to take and process game input, as well as
* handle game output.
*
* @author	Francis Zac dela Cruz
* @since	2015-05-18
*/
public interface SolitaireController {
	/**
	 * Prints the game state.
	 */
	public void printGameState();

	/**
	 * Gets the game input.
	 *
	 * @param o Used in GUI to pass the MouseEvent object.
	 * @return boolean A false indicates either an end of the game (CLI) or an
	 * erroneous move (GUI).
	 */
	public boolean getGameInput(Object o);

	/**
	 * Processes the game input.
	 *
	 * @param input Data representing the game input.
	 * @return The error code (CLI)
	 */
	public int processGameInput(int[] input);
}

package me1.delacruz;
import java.util.Arrays;
import java.util.Scanner;

/**
* <h1>Main</h1>
* The Main class contains the public static void main method. This is where the
* flow of the game and IO is managed.
*
* @author	Francis Zac dela Cruz
* @since	2015-03-26
*/

public class Main {
	/**
	* Main method which handles the CLI and GUI versions of the game, as well as the 
	* game loop of the CLI version. By default, it runs the GUI version.
	* @param args If -no-gui is indicated, the CLI version of the game will run.
	*/
	public static void main(String[] args) {
		if (args.length > 0 && args[0].equals("-no-gui")) {
			SolitaireIO game = new SolitaireCommandLineIO();
			while(game.getGameInput(null)) {}
		} else {
			SolitaireIO game = new SolitaireGraphicalIO();
		}
	}
}

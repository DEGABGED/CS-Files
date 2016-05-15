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
	* Clears the CLI and moves the output to the top of the window.
	* Source: http://stackoverflow.com/questions/4888362/commands-in-java-to-clear-the-screen
	*/
	public static void flush() {
		final String ANSI_CLS = "\u001b[2J";
		final String ANSI_HOME = "\u001b[H";
		System.out.print(ANSI_CLS + ANSI_HOME);
		System.out.flush();
	}

	/**
	* Takes Integer user input and validates it in defense of invalid user input.
	* @return Integer typed in by the user. Returns -1 if input is not integer.
	*/
	public static int numberInput() {
		Scanner sc = new Scanner(System.in);
		try {
			String output = sc.nextLine();
			return Integer.parseInt(output);
		} catch (NumberFormatException n) {
			return -1;
		}
	}

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

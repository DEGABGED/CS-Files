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
	* Main method which contains the game loop. It first prints out the game state,
	* then prompts an integer input corresponding to their preferred course of
	* action. Then, the corresponding game function is executed. Errors in the game
	* are handled and printed out.
	* @param args Unused.
	*/
/*
	public static void main(String[] args){
		Solitaire game = new Solitaire();
		Scanner sc = new Scanner(System.in);
		LinkedStack hand = new LinkedStack();
		System.out.println("~~~~~Welcome!~~~~~");
		int ch = 0;
		int pilenumber = 0;
		int error = 0;
		String dmp; // This string will store unwanted newlines and input.

		flush();
		do {
			error = 0;
			game.printGameState();
			System.out.println("\nHand: " + hand);
			System.out.println("\nWhat would you like to do?");
			System.out.print( "1 - Draw from Stock      "
							+ "2 - Draw from Foundation "
							+ "3 - Draw from a Tableu   \n"
							+ "4 - Draw from Talon      "
							+ "5 - Place on Foundation  "
							+ "6 - Place on a Tableu    \n"
							+ "7 - Throw card from hand "
							+ "8 - Redeal               "
							+ "9 - Reset game           \n"
							+ "10 - Save game           "
							+ "11 - Load game           "
							+ "0 - Quit\n:: ");

			// Check if user input was an integer
			if((ch = numberInput()) == -1) {
				flush();
				System.out.print(String.format(Constant.TEMPLATE, Constant.ERRORS[1]));
				continue;
			}

			if(ch == 0) break;

			// Check if hand is empty
			if(!hand.isEmpty() && (ch < 5 || ch == 8 || ch == 10 || ch == 11)) {
				flush();
				System.out.print(String.format(Constant.TEMPLATE, Constant.ERRORS[2]));
				continue;
			}

			switch(ch) {
				case 1: //Draw from Stock
					hand.push(game.draw());
					break;
				case 2: //Draw from Foundation
					System.out.println("Which foundation?");
					System.out.print("1:"+Constant.SPDS
						+ ", 2:"+Constant.HRTS
						+ ", 3:"+Constant.DMND
						+ ", 4:"+Constant.CLBS
						+ "\n:: ");
					pilenumber = numberInput();
					if(pilenumber < 1 || pilenumber > 4){
						error = 9;
						break;
					}
					hand.push(game.getFromFoundation(Constant.SUITS[pilenumber - 1]));
					break;
				case 3: //Draw from Tableu
					System.out.print("Which tableu pile number?\n:: ");
					pilenumber = numberInput();
					if(pilenumber < 1 || pilenumber > 7){
						error = 9;
						break;
					}
					System.out.print("How many cards?\n:: ");
					int amount = 0;
					if ((amount = numberInput()) == -1) {
						error = 1;
						break;
					}
					hand = game.getFromTableu(pilenumber - 1, amount);
					break;
				case 4: //Draw from Talon
					hand.push(game.getFromTalon());
					break;
				case 5: //Place on Foundation
					if(hand.getSize() > 1) {
						error = 8;
						break;
					}
					if(!hand.isEmpty()) {
						if(!game.moveToFoundation((Card) hand.peek())){
							error = 3;
							break;
						}
						hand.pop();
					}
					break;
				case 6: //Place on Tableu
					System.out.print("Which tableu pile number?\n:: ");
					pilenumber = numberInput();
					if(pilenumber < 1 || pilenumber > 7){
						error = 9;
						break;
					}
					while(!hand.isEmpty()) {
						if(!game.moveToTableu((Card) hand.peek(), pilenumber - 1)){
							error = 4;
							break;
						}
						hand.pop();
					}
					break;
				case 7: //Throw away a card
					game.throwAway((Card) hand.pop());
					break;
				case 8: //Redeal
					if(game.redeal() == -1) {
						error = 6;
					}
					break;
				case 9: //Reset game
					game = new Solitaire();
					hand.clear();
					break;
				case 10: //Save
					System.out.print("Enter the filename:: ");
					if(!game.saveGame(sc.nextLine())) error = 7;
					break;
				case 11: //Load
					System.out.print("Enter the filename:: ");
					if(!game.loadGame(sc.nextLine())) error = 7;
					break;
				default:
					error = 1;
					break;
			}
			// Check if hand has a null card
			if(hand == null || (hand.peek() == null && !hand.isEmpty())) {
				error = 5;
				hand = new LinkedStack();
			}
			flush();
			// Check for and display errors
			if(error != 0) System.out.print(String.format(Constant.TEMPLATE, Constant.ERRORS[error]));
			// Check if the game is already won
			if(game.isWin()) {
				System.out.print(String.format(Constant.TEMPLATE, "YOU WIN!!!"));
				System.out.print("\n\nTry again? (Y/N)\n:: ");
				dmp = sc.nextLine();
				if(dmp.equalsIgnoreCase("y")){
					game = new Solitaire();
					hand.clear();
					flush();
				} else {
					break;
				}
			}
		} while(ch != 0);
	}
*/
	public static void main(String[] args) {
		SolitaireIO game = new SolitaireCommandLineIO();
		while(game.getGameInput()) {}
	}
}

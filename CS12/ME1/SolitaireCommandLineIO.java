package me1.delacruz;
import java.util.Scanner;

public class SolitaireCommandLineIO implements SolitaireIO {
	private SolitaireWrapper game;
	private int error;
	private Scanner sc;
	private int ch;
	private int pilenumber;
	private String dmp;

	public SolitaireCommandLineIO() {
		this.game = new SolitaireWrapper();
		this.error = 0;
		this.sc = new Scanner(System.in);
		this.ch = 0;
		this.pilenumber = 0;
		this.dmp = "";
	}

	/**
	* Clears the CLI and moves the output to the top of the window.
	* Source: http://stackoverflow.com/questions/4888362/commands-in-java-to-clear-the-screen
	*/
	public void flush() {
		final String ANSI_CLS = "\u001b[2J";
		final String ANSI_HOME = "\u001b[H";
		System.out.print(ANSI_CLS + ANSI_HOME);
		System.out.flush();
	}

	/**
	* Takes Integer user input and validates it in defense of invalid user input.
	* @return Integer typed in by the user. Returns -1 if input is not integer.
	*/
	public int numberInput() {
		Scanner sc = new Scanner(System.in);
		try {
			String output = sc.nextLine();
			return Integer.parseInt(output);
		} catch (NumberFormatException n) {
			return -1;
		}
	}

	public void printGameState() {
		int b = 0;
		int fndtotal = 0;

		//Print Stock, Talon, and Foundations
		System.out.println(Constant.STFTOP);
		System.out.print(String.format(Constant.CARDTEXT, (Card) this.game.getStock().peek() == null ? "   " : (Card) this.game.getStock().peek()) +
			String.format(Constant.CARDTEXT, (Card) this.game.getTalon().peek() == null ? "   " : (Card) this.game.getTalon().peek()) + Constant.CARDWIDTH);
		for(LinkedStack x : this.game.getFoundations()){
			System.out.print(String.format(Constant.CARDTEXT, (Card) x.peek() == null ? "   " : (Card) x.peek()));
			fndtotal += x.getSize();
		}
		System.out.print("\n");
		for(b=0; b<3; b++){
			System.out.println(Constant.STFBODY);
		}
		System.out.println(Constant.STFBOTTOM);

		//Print Labels
		System.out.println(" Stock  Talon " + Constant.CARDWIDTH +
			String.format(Constant.CARDMARGIN, Constant.SPDS) +
			String.format(Constant.CARDMARGIN, Constant.HRTS) +
			String.format(Constant.CARDMARGIN, Constant.DMND) +
			String.format(Constant.CARDMARGIN, Constant.CLBS));
		System.out.println(" Redeals left: " + this.game.getRedealsLeft() +
			", Stock: " + this.game.getStock().getSize() +
			", Foundations: " + fndtotal + "\n");
		for(int x=1; x<8; x++){
			System.out.print(String.format(Constant.CARDMARGIN, x));
		}
		System.out.print("\n");

		//Print Tableus
		LinkedStack[] tableuRev = new LinkedStack[7];
		for(b=0; b<7; b++){
			tableuRev[b] = new LinkedStack();
			while(!this.game.getTableus()[b].isEmpty()) tableuRev[b].push(this.game.getTableus()[b].pop());
		}

		boolean someRemain = true;
		while(someRemain){
			someRemain = false;
			for(b=0; b<7; b++){
				if(!tableuRev[b].isEmpty()){
					this.game.getTableus()[b].push(tableuRev[b].pop());
					System.out.print(String.format(Constant.CARDTOPTMPL, (Card) this.game.getTableus()[b].peek()));
					someRemain = true;
				} else  {
					System.out.print(Constant.CARDWIDTH);
				}
			}
			System.out.print("\n");
		}

		System.out.println("MoveStack:");
		System.out.println(this.game.getMoves());
	}

	public boolean getGameInput(Object o) { //returns false only if quit is chosen
		flush();
		do {
			error = 0;
			this.printGameState();
			System.out.println("\nHand: " + game.getHand());
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
				error = 1;
				System.out.print(String.format(Constant.TEMPLATE, Constant.ERRORS[error]));
				continue;
			}

			if(ch == 0) return false;

			// Check if hand is empty
			if(!game.getHand().isEmpty() && (ch < 5 || ch == 8 || ch == 10 || ch == 11)) {
				flush();
				error = 2;
				System.out.print(String.format(Constant.TEMPLATE, Constant.ERRORS[error]));
				continue;
			}

			switch(ch) {
				case 1: //Draw from Stock
					game.draw();
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
					game.getHand().push(game.getFromFoundation(Constant.SUITS[pilenumber - 1]));
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
					game.setHand(game.getFromTableu(pilenumber - 1, amount));
					break;
				case 4: //Draw from Talon
					game.getHand().push(game.getFromTalon());
					break;
				case 5: //Place on Foundation
					if(game.getHand().getSize() > 1) {
						error = 8;
						break;
					}
					if(!game.getHand().isEmpty()) {
						if(!game.moveToFoundation((Card) game.getHand().peek())){
							error = 3;
							break;
						}
						game.getHand().pop();
					}
					break;
				case 6: //Place on Tableu
					System.out.print("Which tableu pile number?\n:: ");
					pilenumber = numberInput();
					if(pilenumber < 1 || pilenumber > 7){
						error = 9;
						break;
					}
					while(!game.getHand().isEmpty()) {
						if(!game.moveToTableu((Card) game.getHand().peek(), pilenumber - 1)){
							error = 4;
							break;
						}
						game.getHand().pop();
					}
					break;
				case 7: //Throw away a card
					while(!game.getHand().isEmpty()) game.throwAway((Card) game.getHand().pop());
					break;
				case 8: //Redeal
					if(game.redeal() == -1) {
						error = 6;
					}
					break;
				case 9: //Reset game
					game = new SolitaireWrapper();
					game.getHand().clear();
					break;
				case 10: //Save
					System.out.print("Enter the filename:: ");
					if(!game.saveGame(sc.nextLine())) error = 7;
					break;
				case 11: //Load
					System.out.print("Enter the filename:: ");
					if(!game.loadGame(sc.nextLine())) error = 7;
					break;
				case 12: // Undo
					game.undo();
					break;
				case 13: // Test moveSingleCard
					System.out.print("Enter src and dest piles:: ");
					int srcp = numberInput();
					int destp = numberInput();
					this.game.moveSingleCard(srcp, destp);
				case 99: // View stacks
					System.out.println("Hand: " + game.getHand());
					System.out.println("Local Hand: " + game.getHand());
					break;
				default:
					error = 1;
					break;
			}
			// Check for face down cards in the tableus
			//if(ch > 4 && ch < 8 && error == 0) game.openTableus();
			// Check if hand has a null card
			if(game.getHand() == null || (!game.getHand().isEmpty() && game.getHand().peek() == null)) {
				System.out.println("Hand is / has null");
				error = 5;
				game.setHand(new LinkedStack());
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
					game = new SolitaireWrapper();
					game.getHand().clear();
					flush();
				} else {
					return false;
				}
			}
		} while(error != 0);
		return true;
	}
}

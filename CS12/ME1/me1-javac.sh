if javac -g -d . Constant.java Suit.java LinkedStack.java Card.java Move.java Solitaire.java SolitaireIO.java SolitaireCommandLineIO.java GUITemplate.java SolitaireGraphicalIO.java Main.java
then
	echo "Successful compilation."
	java me1/delacruz/Main
else
	echo "Error in compilation."
fi

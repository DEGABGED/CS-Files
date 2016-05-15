if javac -g -d . *.java
then
	echo "Successful compilation."
	java me1/delacruz/SolitaireGraphicalIO
else
	echo "Error in compilation."
fi

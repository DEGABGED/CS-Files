if javac -d . *.java -Xlint:unchecked
then
	echo "Successful compilation."
	java me1/delacruz/Main
else
	echo "Error occurred."
fi

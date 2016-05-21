if javac -d . *.java -Xlint:unchecked
then
	echo "Successful compilation."
	java mp1/delacruz/Main
else
	echo "Error occurred."
fi

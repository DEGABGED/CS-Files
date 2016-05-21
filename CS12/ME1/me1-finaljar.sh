if javac -d . *.java -Xlint:unchecked
then
	echo "Successful compilation."
	if jar cfm CS12_MP2_DELACRUZ.jar manifest.txt imagedeck/ me1/delacruz/
	then
		echo 'Successful jarring'
		java -jar CS12_MP2_DELACRUZ.jar
	else
		echo 'Error in jarring'
	fi
else
	echo "Error occurred."
fi

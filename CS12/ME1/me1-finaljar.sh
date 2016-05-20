if javac -d . *.java -Xlint:unchecked
then
	echo "Successful compilation."
	if jar cfm MP2.jar manifest.txt imagedeck/ me1/delacruz/
	then
		echo 'Successful jarring'
		java -jar MP2.jar
	else
		echo 'Error in jarring'
	fi
else
	echo "Error occurred."
fi

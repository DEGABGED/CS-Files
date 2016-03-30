if javac -d . Student.java LinkedList.java MainList.java
then
	echo "Successful compilation."
	java cs12/list/MainList
else
	echo "Error in compilation."
fi

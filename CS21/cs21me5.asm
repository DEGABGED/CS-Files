# CS 21 THWMYZ -- S1 AY 16-17
# Francis Zac dela Cruz	-- 09/12/16
# cs21me5.asm -- Bits and Pieces

.text

main:	li	$v0, 5	# Read integer
	syscall
	move	$t0, $v0
	
	## Create the first output
	ori	$t1, $t0, 0x0FFFFFFF	# Get Region 1 with an OR bitmask such that everything else (in the right) is 1
	srl	$t1, $t1, 14		# Logically shift region 1 to the right such that everything on the left ends up being 0
	
	## Create the second output
	ori	$t2, $t0, 0xF0007FFF	# Get Region 2 with an OR bitmask
	andi	$t3, $t0, 0xF0000000	# Get Region 1 with an AND bitmask; load into $t3
	rol	$t3, $t3, 4		# Rotate $t3 to get the integer equivalent of Region 1
	subi	$t3, $t3, 4		# Since Region 2 is already shifted by 4 bits from the left, subtract 4
	ror	$t2, $t2, $t3		# Rotate Region 2 into position
	
	## Create the third output
	sll	$t3, $t0, 17		# Shift 
	
	## Create the fourth output
	move	$t5, $t0		# Get entire number and load it to $t5 temporarily
	li	$t7, 8			# Set the counter
loop:	beqz	$t7, after		# Exit once the counter is zero. 
					# Cannot check the number itself because edge cases
	andi	$t6, $t5, 0x0000000F	# Get the first digit of $t5 and store to $t6 temporarily
	sll	$t4, $t4, 4		# Shift $t4 to the left by 1 hex digit
	add	$t4, $t4, $t6		# Add the digit to $t4 output
	srl	$t5, $t5, 4		# Shift $t5 to the right to move the last digit
	subi	$t7, $t7, 1		# Decrement the counter
	b	loop
	
after:	li	$t5, 0
	li	$t6, 0
	li	$t7, 0
	li	$v0, 10
	syscall

.data
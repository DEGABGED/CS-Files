# CS 21 THWMYZ -- S1 AY 16-17
# Francis Zac dela Cruz	-- 09/01/16
# cs21me4a.asm -- Conditional and Unconditional Branches: Multiplier

.text

main:	li	$v0, 5		# Read integer
	syscall
	move	$t1, $v0	# Move input to $t1
	li	$v0, 5		# Read second integer
	syscall
	move	$t2, $v0	# Move input to $t2
	beqz	$t1, after
	beqz	$t2, after
	bltz	$t1, then	# If $t1 is negative, then go to 'then'

else:	add	$t3, $t3, $t2	# Add $t2 to $t3
	addi	$t1, $t1, -1	# Decrement $t1 by 1
	bgtz	$t1, else	# If $t1 is greater than or equal to 0, go back to 'else'
	b	after

then:	sub	$t3, $t3, $t2	# Subtract $t2 (factor) from $t3 (product)
	addi	$t1, $t1, 1	# Increment $t1 (factor / counter) by 1
	bltz	$t1, then	# If $t1 is still negative, go back to 'then'

after:	move	$a0, $t3	# Move $t3 (product) to $a0
	li	$v0, 1		# Print integer
	syscall
	li	$v0, 10
	syscall

.data


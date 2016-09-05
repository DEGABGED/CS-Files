# CS 21 THWMYZ -- S1 AY 16-17
# Francis Zac dela Cruz	-- 09/01/16
# cs21me4a.asm -- Conditional and Unconditional Branches: LCM Finder

.text

main:	li	$v0, 5		# Read integer
	syscall
	move	$t1, $v0	# Move input to $t1 and $t4 (for GCF)
	move	$t4, $t1
	li	$v0, 5		# Read second integer
	syscall
	move	$t2, $v0	# Move input to $t2 and $t5 (for GCF)
	move	$t5, $t2
	## Input validation
	blez	$t1, exit
	blez	$t2, exit
	## Find the GCF first (Euclid's); m = $t4, n = $t5, r = $t3
	# Set $t4 to be the smaller one
	slt	$t3, $t4, $t5	# Set $t3 to 0 if $t4 is bigger
	beqz	$t3, then	# Jump to 'then' if $t4 is bigger

else:	move	$t3, $t4	# Else, just set $t3 to $t4 initially
	b	after		# Go to after

then:	move	$t3, $t5	# Switch $t4 and $t5
	move	$t5, $t4
	move	$t4, $t3

after:	# Set $t4 to m, $t5 to n, $t3 to r
	# Divide $t4 by $t5 and set $t3 to be the remainder -> $t5 eventually is the GCF
	move	$t4, $t5
	move	$t5, $t3
	div	$t4, $t5
	mfhi	$t3
	bnez	$t3, after	# Do while remainder is not 0
	move	$t3, $t5	# $t3 is now the GCF
	
	## Find the product of $t1 and $t2
	la	$t4, ($0)	# This time, set $t4 to the future product
	bltz	$t1, thenb	# If $t1 is negative, then go to 'then'

elseb:	add	$t4, $t4, $t2	# Add $t2 to $t4
	addi	$t1, $t1, -1	# Decrement $t1 by 1
	bgtz	$t1, elseb	# If $t1 is greater than or equal to 0, go back to 'else'
	b	afterb

thenb:	sub	$t4, $t4, $t2	# Subtract $t2 (factor) from $t4 (product)
	addi	$t1, $t1, 1	# Increment $t1 (factor / counter) by 1
	bltz	$t1, thenb	# If $t1 is still negative, go back to 'then'
	
afterb:	## Product / GCF
	div	$t4, $t3	# LCM = m*n / GCF
	mflo	$a0		# Get the quotient
	li	$v0, 1		# Print quotient
	syscall

exit:	li	$v0, 10
	syscall

.data

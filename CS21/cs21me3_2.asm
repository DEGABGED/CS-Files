# CS 21 THWMYZ -- S1 AY 16-17
# Francis Zac dela Cruz	-- 09/01/16
# cs21me2.asm -- Hello! The Data Field and Load-Store Operations (lb, lbu, sb)

.text

main:	la	$a0, input	# load addr of input string to $a0
	li	$a1, 8		# 8 chars (6 chars + newline + nullterm)
	li	$v0, 8		# Syscall 8: Read string
	syscall
	
	la	$t2, input	# load addr of input to $t2 (pointer)
	addi	$t2, $t2, 1	# go to the second letter
	lbu	$t3, ($t2)	# load byte from $t2 to $t3 (value)
	addi	$t3, $t3, 0x00000020	# uppercase -> lowercase
	sb	$t3, ($t2)	# store new word from $t3 to $t2
	
	addi	$t2, $t2, 2	# increment pointer by 2 bytes
	lbu	$t3, ($t2)	# load byte from $t2 to $t3 (value)
	addi	$t3, $t3, 0x00000020	# uppercase -> lowercase
	sb	$t3, ($t2)	# store new byte from $t3 to $t2
	
	addi	$t2, $t2, 2	# increment pointer by 2 bytes
	lbu	$t3, ($t2)	# load byte from $t2 to $t3 (value)
	addi	$t3, $t3, 0x00000020	# uppercase -> lowercase
	sb	$t3, ($t2)	# store new byte from $t3 to $t2
	
	la	$a0, input	# load addr of input to $a0
	li	$v0, 4		# Syscall 4: Print String
	syscall
	
	li	$v0, 10
	syscall

.data

input:	.space 8	# Instantiate an 8-character string
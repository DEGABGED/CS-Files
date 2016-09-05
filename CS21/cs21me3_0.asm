# CS 21 THWMYZ -- S1 AY 16-17
# Francis Zac dela Cruz	-- 08/23/16
# cs21me2.asm -- Hello! The Data Field and Load-Store Operations

.text

main:	la	$a0, hello	# load addr of hello into $a0
	li	$v0, 4		# syscall 4: print_string
	syscall
	
	la	$a0, world
	li	$v0, 4
	syscall
	
	la	$t3, hello	# load addr of hello to $t3
	addi	$t3, $t3, 2	# increment t3
	lbu	$t4, ($t3)	# load byte unsigned
	
	la	$a0, ($t3)
	li	$v0, 4
	syscall
	li	$v0, 10
	syscall

.data

hello:	.ascii "H"
	.ascii "e"
	.ascii "l"
	.ascii "l"
	.ascii "o"
	.ascii "\n"
	.byte 0
	.byte 0
	
world:	.asciiz "World\n"
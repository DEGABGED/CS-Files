# CS 21 THWMYZ -- S1 AY 16-17
# Francis Zac dela Cruz	-- 08/23/16
# cs21me2.asm -- Register-to-register; Syscalls

.text

main:	li	$t3, 1		# set $t3 (product) to identity value
	li	$v0, 5		# syscall code 5: integer input
	syscall
	la	$t1, ($v0)	# load value of input to $t1 (input)
	add	$t2, $t1, $t2	# add $t1 and $t2 (sum) and load to $t2
	mult	$t1, $t3	# multiply $t1 and $t3
	mflo	$t3		# get product from $lo and load to $t3
	
	li	$v0, 5		# repeat 4 more times
	syscall
	la	$t1, ($v0)
	add	$t2, $t1, $t2
	mult	$t1, $t3
	mflo	$t3
	
	li	$v0, 5		# repeat 3 more times
	syscall
	la	$t1, ($v0)
	add	$t2, $t1, $t2
	mult	$t1, $t3
	mflo	$t3
	
	li	$v0, 5		# repeat 2 more times
	syscall
	la	$t1, ($v0)
	add	$t2, $t1, $t2
	mult	$t1, $t3
	mflo	$t3
	
	li	$v0, 5		# repeat 1 more time
	syscall
	la	$t1, ($v0)
	add	$t2, $t1, $t2
	mult	$t1, $t3
	mflo	$t3
	
	la	$a0, ($t2)	# loads sum in $t2 to $a0
	li	$v0, 1		# syscall code 1: print integer
	syscall
	li	$a0, 0xA	# loads LF character to $a0
	li	$v0, 11		# syscall code 11: print character
	syscall
	la	$a0, ($t3)	# loads product in $t3 to $a0
	li	$v0, 1
	syscall

	li	$v0, 10		# syscall code 10
	syscall

.data

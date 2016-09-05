# CS 21 THWMYZ -- S1 AY 16-17
# Francis Zac dela Cruz	-- 08/23/16
# mips1.asm -- First one

.text

main:	li	$t1, 9		# load 1 into $t1
	li	$t2, 38
	li	$t3, -421
	li	$t4, 6533
	li	$t5, -1412628480
	li	$v0, 10		# syscall code 10
	syscall

.data
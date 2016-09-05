# CS 21 THWMYZ -- S1 AY 16-17
# Francis Zac dela Cruz	-- 09/01/16
# cs21me2.asm -- Hello! The Data Field and Load-Store Operations (lw, sw)

.text

main:	li	$v0, 8
	la	$a0, input
	li	$a1, 20
	syscall
	
	li	$v0, 4
	la	$a0, hello
	syscall
	
	li	$v0, 4
	la	$a0, input
	syscall
	
	li	$v0, 4
	la	$a0, sayo
	syscall
	
	li	$v0, 10
	syscall

.data

input:	.space 5
hello:	.asciiz "Hello "
sayo:	.asciiz	"Sayounara"
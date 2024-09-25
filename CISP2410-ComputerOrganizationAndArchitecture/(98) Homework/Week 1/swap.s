# Swaps two values using memory addresses; (swap (&num1, &num2))
# Author: amwheeler1
# Register Usage:
#	N/A (see mySwap for registers)

.data
	num1: .quad 10
	num2: .quad 20


.text
.global main
main:
	# subroutine setup and call
	pushq $num1				# push parameter
	pushq $num2				# push parameter
	call mySwap				# call mySwap subroutine
	addq $16, %rsp			# reestablish stack pointer

quit:
	# terminate program
	movq $1, %rax			# rax = 1
	movq $0, %rbx			# rbx = 0
	int $0x80				# system interrupt 0x80
	retq					# return


# mySwap swaps the values of two addresses
# Parameters on stack:
#	$num1
#	$num2
# Returns nothing
# Register Usage:
#	rax, rbx: Holds memory addresses of parameters
#	rcx, rdx: Holds values within paramters' memory addresses
.type mySwap, @function
mySwap:
	# establish stack frame
	pushq %rbp
	movq %rsp, %rbp

	# push registers used
	pushq %rax
	pushq %rbx
	pushq %rcx
	pushq %rdx
	pushfq

	# pull parameters out of stack
	movq 24(%rbp), %rax		# rax = &num1
	movq 16(%rbp), %rbx		# rbx = &num2

	# swap values of Parameters
	movq (%rax), %rcx		# rcx = *(rax)
	movq (%rbx), %rdx		# rdx = *(rbx)
	movq %rcx, (%rbx)		# *(rbx) = rcx
	movq %rdx, (%rax)		# *(rax) = rdx

	# pop registers used
	popfq
	popq %rdx
	popq %rcx
	popq %rbx
	popq %rax
	popq %rbp

	retq					# return
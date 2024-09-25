# How local variables are allocated and used.
# Author: amwheeler1
# Register Usage:
#	rax: Return value of add_nums subroutine.
#	rbx: General-use register in addition subroutine.

.data
	num_A: .quad 18
	num_B: .quad 10
	sum: .quad 0

.text
.global main
main:

	# push parameters to stack
	pushq num_A
	pushq num_B

	call add_nums		# call add_nums subroutine
	addq $16, %rsp		# realign rsp

	movq %rax, sum		# sum = rax

quit:
	movq $1, %rax
	movq $0, %rbx
	int $0x80
	retq
	

# add_nums calculates the sum of two quads
# Parameters on stack:
#	num_A
#	num_B
# Returns sum of num_A and num_B in rax
# Register usage:
#	rbx: General-use register to act as intermediate for addition
.type add_nums, @function
add_nums:

	# establish stack frame
	pushq %rbp
	movq %rsp, %rbp

	# push registers used
	pushq %rbx
	pushfq

	subq $8, %rsp			# allocate 8 bytes for local variables
	movq 16(%rbp), %rbx		# *(rsp + 8) = *(rbp + 16) = num_B
	movq %rbx, 8(%rsp)		# *(rsp + 8) = rbx
	movq 24(%rbp), %rbx		# rbx = *(rbp + 24) = num_A
	addq 8(%rsp), %rbx		# rbx = *(rsp + 8)
	movq %rbx, %rax			# rax = rbx

	# add back size of local variable
	addq $8, %rsp

	# pop registers used in reverse order
	popfq
	popq %rbx
	popq %rbp
	retq
# How subroutines (functions) are called in assembly.
# Author: amwheeler1
# Register Usage:
#

.data
	num: .quad 10
	fac: .quad 0


.text
.global main
main:

# given function: fac = factorial (5);

	movq $5, num			# num = 5
	pushq num				# push num onto stack to pass into subroutine
	call factorial			# call factorial subroutines
	addq $8, %rsp			# add 8 bytes to rsp to move past passed-in value
	movq %rax, fac			# fac = rax (where return value of subroutine went)


.type factorial, @function
factorial:
	
	# subroutine setup

	pushq %rbp
	# rbp (base pointer) establishes the stack frame (portion of the stack used specifically for
	# the subroutine); throughout the execution of the subroutine, rbp will not move, but rsp will
	# change memory values as things are pushed onto the stack

	movq %rsp, %rbp
	# movq the current memory address contained in rsp into rbp to set the start of the subroutine
	# stack frame

	pushq %rdi
	pushq %rbx
	# push registers used in the subroutine onto the stack

	pushfq
	# push flag registers onto the stack

	movq 16(%rbp), %rbx		# rbx = *(rbp + 16) = num = 5
	movq %rbx, %rdi			# rdi = rbx
	movq $1, %rbx			# rbx = 1

forloop:
	cmp $0, %rdi			# rbx ~ 0
	jle endloop				# if rbx <= 0: endloop
	imulq %rdi, %rbx		# rbx *= rdi
	decq %rdi
	jmp forloop

endloop:
	movq %rbx, %rax			# rax = rbx

	# finish subroutine procedures
	popfq					# whatever is pushed onto the stack during the subroutine must be popped
	popq %rbx				# off after execution has been completed, and done in the opposite order
	popq %rdi				# they were pushed as
	popq %rbp

	retq
	# pops an item off the stack and places it in rip (program counter); the value in rip at the end of
	# the subroutine must be the memory location of the next instruction to be executed (in this case
	# the addq $8, %rsp) or the program will crash
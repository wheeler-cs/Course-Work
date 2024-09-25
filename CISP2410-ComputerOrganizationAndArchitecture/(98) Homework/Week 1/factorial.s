# Calculates the factorial of a number (n!); fac = factorial (n)
# Author: amwheeler1
# Register Usage:
#	rax: Holds value of fac before placed in label.

.data
	n: .quad 0
	fac: .quad 0


.text
.global main
main:
	# test if n is valid
	cmp $0, n				# n ~ 0
	jl bad_n				# if n < 0: bad_n

	# factorial subroutine call procedures
	pushq n					# push n to stack
	call factorial			# call factorial subroutine
	addq $8, %rsp			# reestablish stack pointer
	jmp end_program			# go to: end_program

bad_n:
	movq $0, %rax			# rax = 0

end_program:
	# place final resutl into fac
	movq %rax, fac			# fac = rax

	# termiante program
	movq $1, %rax			# rax = 1
	movq $0, %rbx			# rbx = 0
	int $0x80				# system interrupt 0x80
	retq					# return


# factorial calculates the factorial of a number
# Parameters on stack:
#	n
# Returns the factorial of n through rax
# Register Usage:
#	rbx: Holds value of n! as it is calculated.
#	rdi: Acts as index value for number of times loop is executed.
.type factorial, @function
factorial:
	# establish stack frame
	pushq %rbp
	movq %rsp, %rbp

	# push used registers
	pushq %rbx
	pushq %rdi
	pushfq

	# setup for factorial calculation loop
	movq 16(%rbp), %rdi		# rdi = n
	movq $1, %rbx

for_loop:
	cmp $1, %rdi			# rdi ~ 1
	jle end_loop			# if rdi <= 1: end_loop
	imulq %rdi, %rbx		# rbx *= rdi
	decq %rdi				# rdi--
	jmp for_loop			# go to: for_loop
		
end_loop:
	# put final result in return Register
	movq %rbx, %rax

	# pop registers and stack frame
	popfq
	popq %rdi
	popq %rbx
	popq %rbp

	retq					# return
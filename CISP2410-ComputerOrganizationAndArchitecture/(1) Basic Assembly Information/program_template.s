# An assembly program template for the most bare-bones program.
# Author: amwheeler1
# Register Usage:
#	rax: General-use register

# all labels used in the program must be delcared and initialized in the .data section; this excludes
# local variables used in functions
.data
	num1: .quad 0	# num1 is of type quad and contains the value 0

# the actual code of the program is placed in the .text section
.text

# some part of the program must be made available outside so the OS can call the program; the .global
# tag makes the function place after it avaible outside the program, which in this case is main
.global main
main:

	# a basic program that adds two integers together
	movq $10, num1		# num1 = 10
	movq $5, %rax		# rax = 5
	addq num1, %rax		# rax += num1

	# the program termination procedures for an assembly program
	movq $1, %rax		# rax = 1
	movq $0, %rbx		# rbx = 0
	int $0x80			# system interrupt for Linux, tells the program to exit
	retq				# return value of the program, not used on all systems since int $0x80 is used
# Usage of the idivq command.
# Author: amwheeler1
# Register Usage:
#	rax: General register and where quotient is placed after division.
#	rbx: General register.
#	rdx: General register and where remainder is placed after division.

.data
	num1: .quad 0


.text
.global main
main:
	# idivq structure
	#	idivq [denominator]
	#	idivq takes only one operand (the denominator), as registers rax and rdx are used as the
	#	numerator of the division problem

	# idivq quirks
	#	idivq only takes a single operand: the denominator of the division problem
	#	rdx:rax are used as the numerator of the division problem and must be setup before idivq is
	#	used in a program
	#	idivq can only take a register or label/memory as an operand


	# idivq usage:
	#	calculate 31 / 4

	movq $31, %rax			# rax = 31
	# place the number to be divided into rax

	movq %rax, %rdx			# rdx = rax
	# copy the value within rax into rdx

	sarq $63, %rdx
	# shift and rotate the bits within rdx to make it contain only the bit used to represent the sign
	# of the integer held within rax (0 if positive, 1 if negative)

	movq $4, num1			# num1 = 4
	# place the integer inside the register or label used as the denominator

	idivq num1
	# execute the division problem
	# rax = 31 / 4 = 7  <- quotient
	# rdx = 31 % 4 = 3  <- remainder
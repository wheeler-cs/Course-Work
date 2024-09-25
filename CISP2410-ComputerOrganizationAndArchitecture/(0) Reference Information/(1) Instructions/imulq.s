# Usage of the imulq command.
# Author: amwheeler1
# Register Usage:
#	rax, rbx: Used in various examples.

.data
	num1: .quad 0


.text
.global main
main:
	# imulq structure
	#	imulq [operand1], [operand2 & destination]
	#	imulq (integer multiplication quad) is used to multiply two integers together and place the
	#	result in the second operand

	# imulq quirks
	#	imulq has two valid formats:
	#		imulq [label], [register]
	#		imulq [register], [register]
	#	the second operand of imulq MUST BE A REGISTER 
	#	imulq can only take labels/memory and registers as operands

	# valid imulq operations
	imulq num1, %rax		# rax *= num1
	imulq %rax, %rbx		# rbx *= rax

	# invalid imulq operations (WILL CAUSE ERRORS)
	imulq $1, %rax			# rax *= 1
	# literals cannot be used as an operand in imulq

	imulq %rax, num1		# num1 *= rax
	# the result of imulq cannot be placed in a label, it must go to a register
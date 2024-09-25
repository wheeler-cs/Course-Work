# A use-case of the boolean expression operators xorq, andq, and orq.
# Author: amwheeler1
# Register Usage:
#	rax: Used as part of the use-case scenario of the boolean function command.

.data
	num1: .quad 10


.text
.global main
main:
# xorq, andq, and orq are commands that are the equivalent of boolean expressions in boolean algebra
# xorq structure
#	xorq [operand1], [operand2 & destination]
#	xorq performs an exclusive or (XOR) operation between the binary values of the two operands and
#	puts the resulting value in the second operand

# andq structure
#	andq [operand1], [operand2 & destination]
#	andq performs an and (AND) operation between the binary values of the two operands and puts the 
#	resulting value in the second operand 

# orq structure 
#	orq [operand1], [operand2 & destination]
#	orq performs an or (OR) operation between the binary values of the two operands and puts the 
#	resulting value in the second operand 

# usage example:
# obtain the middle bits of the given bit sequence $0xFFF783

	movq $0xFF, %rax		# rax = 0xFF
	# move the hex value of 0xFF (11111111 in binary) into rax

	movq $0xFFF783, num1		# num1 = 0xFFF783
	# move the input value into num1

	shrq $8, num1			# num1 /=2^8
	# shift the value within num1 8 bits to the right
	# 1111 1111 1111 0111 1000 0011 => 1111 1111 1111 0111
	# the lower 8 bits (0x83 or 1000 0011) are truncated, leaving just the higher 16 bits

	andq %rax, num1			# num1 = (num1 & rax)
	# and the value within num1 to rax
	# 1111 1111 1111 0111 & 0000 0000 1111 1111
	# it is assumed that rax has all 0s in the bits leading up to the 0xFF
	# when the value within num1 is AND'd with the value in rax, only the lower 8 bits are kept, since
	# the upper 8 bits of rax are all 0s
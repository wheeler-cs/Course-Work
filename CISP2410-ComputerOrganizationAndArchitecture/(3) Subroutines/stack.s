# An explanation of the stack used to pass information to subroutines (functions).
# Author: amwheeler1
# Register Usage:
#	rax, rbx: General-use registers.

.data
	num1: .quad 15


.text
.global main
main:

	# stacks are last-in first-out memory structures used to pass parameters to subroutines and create
	# local variables; stacks have two operations:
	#	push: pushes a value to the end of the stack
	#	pop: pops a value off the end of the stack
	# a stack pointer (RSP) is used to keep track of the end of the stack; as the stack grows, the
	# memory address gets smaller (i.e. the stack grows down); for a push, something is subtracted from
	# RSP; for a pop, something is added to RSP

	# Ex.
	# Given:
	#
	#		| Address | Stack |
	#		| 0xEBF9  |   ?   |
	#  RSP >| 0xEBF8  |   ?   |
	#		| 0xEBF7  |   ?   |
	#		| 0xEBF6  |   ?   |
	#		| 0xEBF5  |   ?   |
	#		| 0xEBF4  |   ?   |
	# current RSP: 0xEBF8
	#
	#		movq $-1, %rax
	#		pushq %rax
	#
	#		| Address | Stack |
	#		| 0xEBF9  |   ?   |
	#		| 0xEBF8  |   ?   |
	#		| 0xEBF7  |  0xFF |
	#		| 0xEBF6  |  0xFF |
	#		| 0xEBF5  |  0xFF |
	#		| 0xEBF4  |  0xFF |
	#		| 0xEBF3  |  0xFF |
	#		| 0xEBF2  |  0xFF |
	#		| 0xEBF1  |  0xFF |
	#  RSP >| 0xEBF0  |  0xFF |
	# current RSP: 0xEBF0
	#
	# pushq has pushed the value within rax (in this case a quad value of -1) onto the stack; the
	# amount of space allocated within the stack is the same as the size of the data type (quad has a
	# size of 8 bytes, so 8 bytes were filled)
	#
	# current RSP: 0xEBF0
	#
	#		movw $16, %ax
	#		pushw %ax
	#
	# a word in this case is 2 bytes (16 bits) in size, so that is the space allocated on the stack;
	# since the value is multiple bytes in size, the higher-order bits are stored in the higher
	# memory address (0xEBEF) and the lower-order bits are stored in the lower memory address (0xEBEE)
	#
	#		| Address | Stack |
	#		| 0xEBF9  |   ?   |
	#		| 0xEBF8  |   ?   |
	#		| 0xEBF7  |  0xFF |
	#		| 0xEBF6  |  0xFF |
	#		| 0xEBF5  |  0xFF |
	#		| 0xEBF4  |  0xFF |
	#		| 0xEBF3  |  0xFF |
	#		| 0xEBF2  |  0xFF |
	#		| 0xEBF1  |  0xFF |
	#		| 0xEBF0  |  0xFF |
	#		| 0xEBEF  |  0x00 |
	#  RSP >| 0xEBEE  |  0x10 |
	# current RSP: 0xEBEE
	#
	# for a value to be taken out of the stack, the pop command that is used must take off the same
	# number of bits as the data type
	#
	# popw %bx
	#
	# the number of bits that correspond to that data type are copied to the destination specificied
	# by the pop command and the RSP is moved that many bytes
	#
	#		| Address | Stack |
	#		| 0xEBF9  |   ?   |
	#		| 0xEBF8  |   ?   |
	#		| 0xEBF7  |  0xFF |
	#		| 0xEBF6  |  0xFF |
	#		| 0xEBF5  |  0xFF |
	#		| 0xEBF4  |  0xFF |
	#		| 0xEBF3  |  0xFF |
	#		| 0xEBF2  |  0xFF |
	#		| 0xEBF1  |  0xFF |
	#  RSP >| 0xEBF0  |  0xFF |
	#		| 0xEBEF  |  0x00 |
	#		| 0xEBEE  |  0x10 |
	# current RSP: 0xEBF0
	#
	# the values inside the memory address are not cleared out when something is popped off the stack,
	# instead the RSP moves the number of bytes it needs to and if that memory space needs to be used
	# again, the values inside will be overwritten when something is pushed onto the stack
	#
	# popq %rcx
	#
	#		| Address | Stack |
	#		| 0xEBF9  |   ?   |
	#  RSP >| 0xEBF8  |   ?   |
	#		| 0xEBF7  |  0xFF |
	#		| 0xEBF6  |  0xFF |
	#		| 0xEBF5  |  0xFF |
	#		| 0xEBF4  |  0xFF |
	#		| 0xEBF3  |  0xFF |
	#		| 0xEBF2  |  0xFF |
	#		| 0xEBF1  |  0xFF |
	#		| 0xEBF0  |  0xFF |
	#		| 0xEBEF  |  0x00 |
	#		| 0xEBEE  |  0x10 |
	# current RSP: 0xEBF8
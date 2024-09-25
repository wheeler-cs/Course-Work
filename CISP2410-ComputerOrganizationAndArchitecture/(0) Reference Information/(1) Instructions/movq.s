# A description of the movq command used to transfer data between registers
# and memory.
# Author: amwheeler1
# Register Usage:
#	rax, rbx: Registers used in various examples.

.data
	num1: .quad 10
	array1: .quad 1, 2, 3, 4, 5


.text
.global main
main:

#movq Structure
	# movq source, destination
	# movq moves data from the "source" variable to the "destination" variable

#Valid movq Operations
	movq $1, num1		# num1 = 1
	movq $-1, num1		# num1 = -1
	movq num1, %rbx		# rbx = num1
	movq %rax, num1		# num1 = rax
	movq $array1, %rax	# rax = &array1 (address of array 1)
	
#Invalid movq Operations (WILL CAUSE ERRORS)
	movq num1, $1		# 1 = num1
	# Attempt to assign the value of a label within a literal
	# "operand size mismatch for movq"
	
	movq num1, num2		# num2 = num1
	# Only a single label (i.e. memory location) can be used as an operand
	# "too many memory references for movq"
	# This concept applies to several different commands; values must be
	# placed in registers first, then into labels
	
	#Terminate Program Execution
	movq $1, %rax
	movq $0, %rbx
	int $0x80
	retq

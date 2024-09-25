# An assembly program explaing various basic modes of addressing.
# Author: amwheeler1
# Register Usage:
#	rax: General-use register used in various examples.

.data
	num1: .quad 0
	array: .zero 10


.text
.global main
main:
	
	# immediate addressing
	addq $1, %rax
	# using $1 is immediate addressing, meaning a constant is used 

	# register addressing
	addq $10, %rax
	# using the % symbol indicates addressing a register

	# direct addressing
	addq num1, %rax
	# a label or memory address is used, in this case, num1 is a label to some place in memory

	# register indirect addressing
	movq $array, %rax		# rax = &array
	movq $5, (%rax)			# *rax = array[0] = 5
	# a register is used as a pointer to some address, and the value within that address is manipulated
	# using that register; useful for passing parameters to functions by reference or indexing through
	# an array

	# indexed addressing
	# there are two main kinds:
	#	register indirect with displacement
		movq $array, %rax		# rax = &array
		movq $2, 8(%rax)		# *(rax + 8 bytes) = array[1] = 2
		movq $16, (%rbx)		# rbx = 16
		movq $3, (%rax, %rbx)	# *(rax + rbx) = *(rax + 16 bytes) = array[2] = 3
	#	register indirect with displacement tends to be used for accessing the elements of arrays
	#
	#	register indirect with displacement and scale
		movq $3, %rdi				# rdi = 3
		movq $4, (%rax, %rdi, 8)	# *(rax + rdi*8) = *(rax + 24) = array [3] = 4
		incq %rdi					# rdi++
		movq $5, array(, %rdi, 8)	# &array + rdi*8 = &array + 32 = array[4] = 5
	#	register indirect with displacement and scale tends to be used for accessing elements of arrays
	#	and elements of arrays of structures
	#	rdi is used as an index for the array
	#
	#	in both of these examples 8 is used because that is the size (in bytes) of the .quad data
	#	type; the displacement value must match the size of the data type in bytes in order for the
	#	next element to be addressed (i.e. any other number except a multiple of 8 as the displacement
	#	is going to cause problems)
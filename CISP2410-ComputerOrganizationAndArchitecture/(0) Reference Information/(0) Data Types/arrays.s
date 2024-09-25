# A program explaining the syntax and usage of arrays in assembly language.
# Author: amwheeler1
# Register Usage:
#	rax, rbx: Registers used to hold array pointers
#	rcx: Register used as a miscellaneous data holder

.equ NUM_ELEMENTS, 5		# assembly has preprocessor directives that can be used to define constants

.data
	myArray: .zero NUM_ELEMENTS		# arrays are declared and initialized just like normal labels,
	# with a label name, data type, and initial value; in the case of arrays, the initial value
	# is typically the size of the array (in this case NUM_ELEMENTS = 5); the .zero data type tells
	# the computer to fill all elements with 0

	myArray2: .quad 5, -1, 4, 3, 99, 2, -25, 42, 10, -9		# arrays can also have their elements
	# initialized to specific value, doing this will serve two purposes:
	#	1. Specify the size of the array by the number of variables listed
	#	2. Initialzie all of the elements within the array to a specific value
	# in this case myArray2 has been given a size of 10 elements, and each of those elements has been
	# given a unique value


.text
.global main
main:
	movq $myArray, %rax		# rax = &myArray (rax = address of myArray[0])
	movq $myArray2, %rbx	# rbx = &myArray2 (rbx = address of myArray2[0])

	# once the array address has been assigned, whatever holds that address can be used like a pointer
	# to access that array's [0] element
	movq $5, (%rax)			# *(rax) = myArray[0] = 5

	# to access more elements of an array, the size of the data type being used must be known; 
	# accessing elements past [0] is done by offsetting the pointer the same number of bits that is the
	# size of the data type of the array; in this case, .quads (which is 8 bytes) are being used, so
	# the offset must be 8 bytes to reach the next element
	movq $12, 8(%rax)		# *(rax+8 bytes) = array[1] = 12
	
	movq $16, %rcx			# rcx = 16
	movq $99, (%rax,%rcx)	# *(%rax+%rcx) = *(%rax+16 bytes) = myArray [2] = 99
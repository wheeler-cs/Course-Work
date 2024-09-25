# A description of the cmp command used to compare two values.
# Author: amwheeler1
# Register Usage:
#	rax, rbx: General-use registers

.data
	num1: .quad 0


.text
.global main
main:
	
# cmp structure
#	cmp [operand1], [operand2]
#	compares the two operands and sets a flag register based on their relation

# cmp quirks
#	operand1 can be a register, label/memory, or a literal
#	operand2 can only be a register or label/memory

	cmp %rbx, %rax		# compare rbx to rax
	je same_num			# if rax == rbx; jump to sameNum
	jmp quit			# jump to quit

same_num:			# rbx and rax are same num
	incq %rax			# rax++

quit:				# program termination procedures
	movq $1, %rax
	movq $0, %rbx
	int $0x80
	retq
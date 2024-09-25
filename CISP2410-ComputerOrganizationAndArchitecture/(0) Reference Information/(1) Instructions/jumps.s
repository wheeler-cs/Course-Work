# Information regarding the several types of jump commands.
# Author: amwheeler1
# Register Usage:
#	rax, rbx: General-use registers

.data
	num1: .quad 0


.text
.global main
main:

	movq $5, %rax
	movq $7, %rbx

	# cmp must first be used to set the flag register for how the two values relate
	cmp %rax, %rbx		# rbx ~ rax
	# the second operand will be used as the left-handed variable in any logical comparison

	# all jump commands follow the same format of [jumpType] [labelToJumpTo]

	# je (jump if equal)
	je equal_num		# rbx == rax

	# jne (jump if not equal)
	jne not_equal		# rbx != rax

	# jg (jump if greater than)
	jg greater_than		# rbx > rax

	# jl (jump if less than)
	jl less_than		# rbx < rax

	# jge (jump if greater than or equal)
	jge greater_equal	# rbx >= rax

	# jle (jump if less than or equal)
	jle less_equal		# rbx <= rax

	# jmp (unconditional jump)
	jmp quit			# jump to quit


equal_num:
	incq %rax			# rax++
	jmp quit

not_equal:
	decq %rax			# rax--
	jmp quit

greater_than:
	movq %rax, %rbx		# rbx = rax
	jmp quit

less_than:
	movq %rbx, %rax		# rax = rbx
	jmp quit

greater_equal:
	movq $5, %rax		# rax = 5
	jmp quit

less_equal:
	movq $5, %rbx		# rbx = 5
	jmp quit

quit:
	movq $1, %rax		# rax = 1
	movq $0, %rbx		# rbx = 0
	int $0x80			# system interrupt 0x80
	retq				# return
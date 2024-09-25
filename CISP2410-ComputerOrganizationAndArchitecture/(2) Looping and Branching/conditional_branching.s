# A program explaining how conditional branching and looping works in assembly.
# Author: amwheeler1
# Register Usage:
#	rax, rbx: General-use registers

.equ VALUE_A, 15
.equ VALUE_B, 10

.data
	pass_count: .quad 0


.text
.global main
main:
	
# conditional branching and looping is done when the program needs to make a decision on how to execute
# based on how two values compare; this is implemented with the cmp command followed by one of the many
# types of jump commands

	movq $VALUE_A, %rax		# rax = VALUE_A
	movq $VALUE_B, %rbx		# rbx = VALUE_B

loopstart:
	incq pass_count			# pass_count++
	cmp %rbx, %rax			# rax ~ rbx
	je quit					# if rax == rbx: quit
	jl incrrax				# if rax < rbx: incrrax
	jmp decrrbx		    	# else: decrrbx

incrrax:
	incq %rax				# rax++
	jmp loopstart			# go to: loopstart

decrrbx:
	decq %rax				# rax--
	jmp loopstart			# go to: loopstart

quit:
	movq $1, %rax			# rax = 1
	movq $0, %rbx			# rbx = 0
	int $0x80				# system interrupt 0x80
	retq
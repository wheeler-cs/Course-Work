# a program that sorts an array with a preset size and element values
# author: amwheeler1
# register usage:
#	  %rsp: register stack pointer restored in main
#	  %rax, %rbx: used in program termination sequence in main


.equ NUM_ELEMENTS, 10
.data
	myArray: .quad 5, -1, 4, 55, -30, 2, 1, 9, -55, 10


.text
.global main
main:
	# mySort subroutine
	pushq $myArray			  # push myArray[0]
	pushq $NUM_ELEMENTS		# push NUM_ELEMENTS
	call mySort		    	  # call mySort subroutine
	addq $16, %rsp			  # re-establish stack pointer

quit:
	# terminate program execution
	movq $1, %rax			    # rax = 1
	movq $0, %rbx			    # rbx = 0
	int $0x80			        # system interrupt 0x80
	retq				          # return

# mySort subroutine sorts an array's element values
# parameters on stack:
#	myArray: address of first element of array to be sorted
#	NUM_ELEMENTS: size of array
# returns: nothing as array is passed by reference
# register usage:
#	%rbp: base pointer of stack frame
#	%rsp: stack pointer to maintain stack position
#	%rbx: stores myArray[0]
#	%rcx: used as temp location
#	%rdi: stores NUM_ELEMENTS; iterator in for_loop
#	%r8 : used as myArray[i-1]
#	%r9 : used as myArray[i]
#	
.type mySort, @function			# mySort (myArray, NUM_ELEMENTS)
mySort:
	# establish stack frame
	pushq %rbp		        # push base pointer
	movq %rsp, %rbp       # base pointer = stack pointer

	# push registers used
	pushq %rbx			      # push rbx
	pushq %rcx		      	# push rcx
	pushq %rdi		      	# push rdi
	pushq %r8			        # push r8
	pushq %r9			        # push r9
	pushfq				        # push flag register

	movq 24(%rbp), %rbx		# rbx = myArray[0]
	movq 16(%rbp), %rdi		# rdi = NUM_ELEMENTS
	decq %rdi		        	# rdi--
	movq %rbx, %r8

for_loop:
	# determine if loop should end (rdi < 0)
	cmp $1, %rdi		  	  # rdi ~ 1
	jl end_sort			      # if rdi < 2: end_sort

	# setup registers for comparison
	movq %rbx, %r9			  # r9 = &myArray[0] (%rbx)
	movq %rbx, %r8			  # r8 = &myArray[0] (%rbx)

	# rcx = i
	movq %rdi, %rcx			  # rcx = rdi
	imulq $8, %rcx			  # rcx *= 8

	# set r9 and r8 to i and i-1 by offsetting from myArray[0]
	addq %rcx, %r9			  # r9 = myArray[i] (rcx)
	subq $8, %rcx			    # rcx = i-1
	addq %rcx, %r8			  # r8 = myArray[i-1] (rcx)

	# determine if values should be swapped
	movq (%r9), %rcx		  # rcx = *r9
	cmp (%r8), %rcx			  # rcx ~ r8
	jge no_swap			      # if r9 >= r8: no_swap 

	# swap values
	pushq %r8			        # push &elementA
	pushq %r9			        # push &elementB
	call mySwap			      # call mySwap subroutine
	addq $16, %rsp			  # re-establish stack pointer

	# add 2 to rdi if a swap occurs so next higher value can be compared
	addq $2, %rdi			    # rdi += 2
	cmp $10, %rdi			    # rdi ~ 10
	jle no_swap			      # if rdi <= 10: no_swap
	decq %rdi			        # rdi--

no_swap:
	# next loop iteration
	decq %rdi			        # rdi--
	jmp for_loop			    # go to: for_loop

end_sort:
	# pop registers used
	popfq				          # pop flag register
	popq %r9			        # pop r9
	popq %r8			        # pop r8
	popq %rdi			        # pop rdi
	popq %rcx			        # pop rcx
	popq %rbx			        # pop rbx
	pop %rbp			        # pop base pointer
	retq				          # return

# mySwap subroutine swaps the values contained in two memory addresses
# parameters on stack:
#	&elementA: address of first value to be swapped
#	&elementB: address of second value to be swapped
# returns: nothing as both values are passed by reference
# register usage:
#
.type mySwap, @function			# mySwap (&ele1, &ele2)	
mySwap:
	# establish stack frame
	pushq %rbp			      # push base pointer
	movq %rsp, %rbp			  # base pointer = stack pointer

	# push registers used
	pushq %rax			      # push rax
	pushq %rcx			      # push rcx
	pushq %rdx			      # push rdx
	pushq %r10			      # push r10
	pushfq				        # push flag register

	# get parameters
	movq 24(%rbp), %rax		# rax = &elementA
	movq 16(%rbp), %rdx		# rdx = &elementB

	# swap values in rax and rdx
	movq (%rax), %rcx		  # rcx = *rax
	movq (%rdx), %r10	  	# r10 = *rdx
	movq %r10, (%rax)	  	# *rax = r10
	movq %rcx, (%rdx)		  # *rdx = rcx

	# pop registers used
	popfq				        # pop flag register
	popq %r10			      # pop r10
	popq %rdx			      # pop rdx
	popq %rcx			      # pop rcx
	popq %rax			      # pop rax
	pop %rbp			      # pop base pointer
	retq				        # return

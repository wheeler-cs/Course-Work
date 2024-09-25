# Calculate the miles-per-gallon of a vehicle, assuming gallons and miles are given.
# (mpg = miles / gallons) w/ rounding
# Author: amwheeler1
# Register Usage:
#	rax: Used in division as quotient
#	rdx: Used in division as remainder

.data
	miles: .quad 0
	gallons: .quad 0
	mpg: .quad 0

.text
.global main
main:
	# prepare registers for division
	movq miles, %rax		# rax = miles
	movq %rax, %rdx			# rdx = rax
	sarq $63, %rdx			# shift and rotate rdx

	# calculate fuel to distance ratio
	idivq gallons			# rdx:rax / gallons

	# determine rounding rules
	imulq $2, %rdx			# rdx *= 2
	cmp gallons, %rdx		# rdx ~ gallons
	jg round_up				# if rdx > gallons: round_up
	jmp end_program			# go to: end_program

round_up:
	incq %rax				# rax++

end_program:
	# move final result into mpg
	movq %rax, mpg			# mpg = rax

	# terminate program
	movq $1, %rax			# rax = 1
	movq $0, %rbx			# rbx = 0
	int $0x80				# system interrupt 0x80
	retq					# return
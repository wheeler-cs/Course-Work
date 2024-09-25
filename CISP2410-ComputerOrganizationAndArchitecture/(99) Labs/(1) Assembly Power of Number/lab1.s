# A program that calculates x^y and puts the result in p
# Author: amwheeler1
# Register Usage:
#   rax: return value of power subroutine

.data
    x: .quad 0
    y: .quad 0
    p: .quad 0
    
    
.text
.global main
main:
    # test for valid variables
    cmp $0, x               # x ~ 0
    jl bad_val              # if x < 0: bad_val
    cmp $0, y               # y ~ 0
    jl bad_val              # if y < 0: bad_val
    
    # power subroutine
    pushq x                 # push x to stack as subroutine parameter
    pushq y                 # push y to stack as subroutine parameter
    call power              # call power subroutine
    addq $16, %rsp          # readjust stack pointer after parameter push
    movq %rax, p            # place return of subroutine into p
    jmp quit                # go to: quit
    
bad_val:
    # p defaults to 0 is x or y is negative
    movq $0, p              # p = 0

quit:
    # program termination procedures
    movq $1, %rax           # rax = 1
    movq $0, %rbx           # rbx = 0
    int $0x80               # system interrupt 0x80
    retq                    # return
    
    
# Power subroutine calculates x^y and returns calculated value
# Parameters on stack:
#   x: base
#   y: exponent
# Returns calculated power through rax
# Register usage:
#   rbx: holds value of base to be multiplied with rax every loop cycle
#   rdi: holds exponent value to be used as loop index
#
.type power, @function
power:
    # establish stack frame
    pushq %rbp              # push rbp to stack
    movq %rsp, %rbp         # rbp = rsp
    
    # push registers used for subroutine
    pushq %rdi              # push index register (register to contain power)
    pushq %rbx              # push rbx (register to contain base)
    pushfq                  # push flag registers
    
    # setup registers for calculation
    movq 16(%rbp), %rdi     # rdi = y
    movq 24(%rbp), %rbx     # rbx = x
    movq $1, %rax           # rax = 1
    
for_loop:
    # calculate power
    cmp $0, %rdi            # rdi ~ 0
    jle end_loop            # if rdi <= 0: end_loop
    imulq %rbx, %rax        # rax *= rbx
    decq %rdi               # rdi--
    jmp for_loop            # go to: for_loop (restart loop)
    
end_loop:
    # pop used registers in reverse order
    popfq                   # pop flag registers
    popq %rbx               # pop rbx
    popq %rdi               # pop rdi
    popq %rbp               # pop rbp
    
    retq                    # return

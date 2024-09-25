# An assembly implementation of for (int i = i; i < max; i++) sum += i;
# Author: amwheeler1
# Register Usage:
#   %rdi: Used as the iterator of the loop (i)
#   %rax: Used as an intermediate and evenutally put into sum

.data
    sum: .quad 0        # sum of loop
    max: .quad 10       # upper loop execution count

.text
.global main
main:
    movq $0, %rdi       # rdi = 0
    movq $0, %rax       # rax = 0
    
forloop:                # main body of for loop
    cmp max, %rdi       # if rdi >= max
    jge endloop         # jump to endloop
    addq %rdi, %rax     # rax += rdi
    incq %rdi           # rdi++
    jmp forloop         # restart forloop
    
endloop:                # end of loop
    movq %rax, sum      # sum = rax
    
quit:                   # exit program
    movq $1, %rax       # rax = 1
    movq $0, %rbx       # rbx = 0
    int $0x80           # system interrrupt 0x80
    retq                # return

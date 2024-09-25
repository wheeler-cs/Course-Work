# Program adds 2 numbers together and stores the sum
# Author: amwheeler1
# Register Usage:
#   rax used to calculate sum

# Data portion of program used to declare labels and their values
.data
    num1: .quad 4       # num1 = 4
    num2: .quad -1      # num2 = -1
    sum: .quad 0        # sum = 0
# .quad is a keyword used to indicate that the date within the labels is
# a quad-word (8 bytes in size)
# In the case of this program, labels are 8-byte, two's complement numbers

# Text portion of the program used to indicate where execution begins
.text

# .global main indicates that main is acessible outside the current file
.global main

# Begin execution of main
main:

    # Add two numbers together
    #movq: Move quad word
    movq num1, %rax     # %rax = num1
    #addq: Add quad word
    addq num2, %rax     # %rax = %rax + num2
    movq %rax, sum      # sum = %rax
    
    # Call exit to quit program execution
    movq $1, %rax       # %rax = $1
    #Value within %rbx is what the system returns (if applicable)
    movq $0, %rbx       # %rbx = $0
    int $0x80           # Interrupt: Linux system call to interrupt vector
    # For this particular example when int $0x80 is called, a value of $1 in
    # %rax indicates an exit, and %rbx=0 is the value returned
    
    retq                # Return (not really needed since their is a Linux
                        # system call, but is good practice to have)

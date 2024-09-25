# A description of the addq and subq commands used to perform basic arithmetic.
# Author: amwheeler1
# Register Usage:
#   rax: Used in various examples


.data
    num1: .quad 10
    num2: .quad 5
    
    
.text
.global main
main:

# addq structure
#   addq [operand1], [operand2 & destination]
#   addq adds the second operand to the second operand and places the sum in 
#   the second operand

# subq structure
#   subq [operand1], [operand2 & destination]
#   subq subtracts the first operand from the second operand and places the
#   difference in the second operand

# valid addq and subq operations
    addq $15, num1      # num1 += 15
    addq %rax, num1     # num1 += rax
    subq num2, %rax     # rax -= num2
    subq $12, %rax      # rax -= 12
    
# invalid addq and subq operations (WILL CAUSE ERRORS)
    subq num1, num2     # num2 -= num1
    # cannot use two memory addresses as operands
    
    addq %rax, $15      # 15 += rax
    # cannot have a literal as the destination

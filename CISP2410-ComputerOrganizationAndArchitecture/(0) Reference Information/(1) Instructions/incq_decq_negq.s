# A description of the incq, decq, and negq commands used to manipulate
# integer values.
# Author: amwheeler1
# Register Usage:
#    rax: Used in various examples.


.data
    num1: .quad 10
    

.text
.global main
main:

# incq Structure
    # incq [value]
    # incq increments an integer value by 1
    
# decq Structure
    # decq [value]
    # decq decrements an integer value by 1
    
# valid incq and decq operations
    incq num1       # num1++
    decq %rax       # rax--
    
# invalid incq and decq operations (WILL CAUSE ERRORS)
    decq $50        # 50--
    # cannot increment or decrement a literal
    
    
# negq Structure
    # negq [value]
    # negq negates an integer value by 1
    
# valid negq operations
    negq num1       # num1 = -num1
    negq %rax       # rax = -rax
    
# invalid negq operations (WILL CAUSE ERRORS)
    negq $num1      # &num1 = -&num1
    # cannot negate a static memory address
    # "operand mismatch for neg"

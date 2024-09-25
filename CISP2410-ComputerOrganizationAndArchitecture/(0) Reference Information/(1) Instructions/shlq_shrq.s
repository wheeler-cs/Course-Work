# A description of the shrq and shlq bit-shifting commands.
# Author: amwheeler1
# Register Usage:
#   rax: Used in various examples


.data
    num1: .quad 50
    
    
.text
.global main
main:

# shrq structure
#   shrq [offset], [input & destination]
#   shrq performs a binary operation where the bits of the value within the
#   input are shifted to the right the number of places indicated by offset;
#   low-order bits are truncated and high-order bits are initialized to 0

# shlq structure
#   shlq [offset], [input & destination]
#   shlq performs a binary operation where the bits of the value within the
#   input are shifted to the left the number of places indicated by offset;
#   high-order bits are truncated and low-order bits are initialized to 0

# valid shrq and shlq operations
    shrq $4, %rax       # rax /= 2^4
    shlq $3, num1       # num1 *= 2^3
    
# invalid shrq and shlq operations (WILL CAUSE ERRORS)
    shrq num1, %rax     # rax /= 2^num1
    #cannot use a label or indeterminate value as the offset
    
    
# an in-depth look at shrq and shlq
#   shrq example:
#       binary input: 00110011
#       offset input: $3
#       *assume the size of all binary values is a single byte
#
#       00110011 / 2^3 = 00110 (low-order bits are truncated)
#       00000110 (high-order bits are initialized to 0)
#       final result: 00000110
#
#   shlq example:
#       binary input: 00001011
#       offset input: $2
#       *assume the size of all binary values is a single byte
#
#       00001011 * 2^2 = 0000101100 (low-order bits are initialized to 0)
#       00101100 (high-order bits are truncated)
#       final result: 00101100

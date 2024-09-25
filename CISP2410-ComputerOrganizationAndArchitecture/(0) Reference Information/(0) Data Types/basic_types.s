# A file explaining the various data types available for use in assembly.
# Author: amwheeler1

# the "variables" of assembly are all declared in the .data section of the program
.data

# these "variables" (also called labels) use the following format to declare their name,
# data type, and initial value:
#    [label]: [type] [initial value]
    num1: .quad 10      # labels do not need a literal tag ($) before their value during initialization
    
# each data type available in assembly has a binary size that specifies how much memory it takes up
#
# ascii     text string (variable size)
# .asciz    null-terminated text string (variable size)
# .byte     single-byte (1 byte, 8 bits)
# .double   double-precision floating-point (8 bytes, 64 bits)
# .float    single-precision floating-point (4 bytes, 32 bits)
# .int      integer (4 bytes, 32 bits)
# .long     integer (4 bytes, 32 bits; same as .int)
# .octa     integer (16 bytes, 128 bits)
# .quad     integer (8 bytes, 64 bits)
# .short    integer (2 bytes, 16 bits)
# .sing     single-precision floating-point (4 bytes, 32 bits)

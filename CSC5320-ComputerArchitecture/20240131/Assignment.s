.data
    ax: .word 5 # uint32_t ax[5]
    hello_world: .string "Hello World!" # char *hello_world = "Hello World!"

.text

# Problem 1: If statement
# int a,b,c;
# int main(){
#   if(a > 0){
#       b = 22;
#   }
# }
main_1:
    li t0, 1                # a = 1
    li t1, 0                # b = 0 (Default)
    ble t0, zero, end_1     # if: a > 0, else: goto end_1
    li t1, 22               #   b = 22
end_1:
    nop # Pause here to allow for debugging


# Problem 2: While loop
# i = 0
# while i < 10
#   i = i + 1
main_2:
    li t0, 0            # i = 0
    li t1, 10           # lim = 10
loop_start_2:
    bge t0, t1, end_2   # if: i < 10, else: goto end_2
    addi t0, t0, 1      #   i += 1
    j loop_start_2      # goto loop_start
end_2:
    nop # Pause here to allow for debugging


# Problem 3: Summation without array
# int a, b, c;
# int main() {
#   sum = a + b +c;
# }
main_3:
    li t0, 1        # a = 1
    li t1, 2        # b = 2
    li t2, 3        # c = 3
    add t3, t0, t1  # sum = a + b
    add t3, t2, t3  # sum += c
    nop # Pause here to allow for debugging


# Problem 4: Summation using array
# ax[5]
# s = 0
# i = 0
# while i < 5
#   s = s + ax[i]
#   i = i + 1
main_4:
    la t0, ax       # Store pointer to ax[0] in t0
    li t1, 0        # s = 0, sum
    li t2, 0        # i = 0, iterator
    li t3, 5        # lim = 5 (size of ax)
setup_array_4: # Sets the array elements
    # ax[0] = 2
    li t4, 2
    sw t4, 0(t0)
    # ax[1] = 4
    li t4, 4
    sw t4, 4(t0)
    # ax[2] = 8
    li t4, 8
    sw t4, 8(t0)
    # ax[3] = 16
    li t4, 16
    sw t4, 12(t0)
    # ax[4] = 32
    li t4, 32
    sw t4, 16(t0)
loop_start_4:
    bge t2, t3, end_4   # if i > 5: goto end_4
    lw t4, 0(t0)        # Get value within ax[i]
    add t1, t1, t4      # s += ax[i]
    addi t0, t0, 4      # ax_ptr += sizeof(word)
    addi t2, t2, 1      # i++
    j loop_start_4      # goto loop_start_4
end_4:
    nop # Pause here to allow for debugging


# Problem 5: Print "Hello World"
# print("Hello World!")
main_5:
    addi a0, x0, 4      # Specify string to be printed
    la a1, hello_world  # a1 = &"Hello World!"
    ecall               # print(*a1)
end_5:
    nop # Pause here to allow for debugging


# Problem 6: Reverse the string "Hello, World!"
main_6:
    nop


# Problem 7: Implement subroutines
# int twice(int x){
#   return( x + x);
# }
# int main(){
#   int a;
#   a = twice(2);
# }
main_7:
    nop



# Problem 8: Solve a = b + c + d + e - f using any values
main_8:
    nop


# Problem 9: Swap the values of two variables
main_9:
    addi t0, x0, 5 # a = 5
    addi t1, x0, 6 # b = 6
    add t2, x0, t0 # temp = a
    add t0, x0, t1 # a = b
    add t1, x0, t2 # b = temp
    nop


# Problem 10: Calculate 10! (factorial)
main_10:
    addi t0, x0, 10 # mult = 10
    addi t1, x0, 1  # factorial = 1
factorial_loop:
    ble t0, x0, end_10 # if mult <= 0, goto: end_10
    mul t1, t1, t0     # factorial *= mult
    addi t0, t0, -1    # mult--
    j factorial_loop   # goto: factorial_loop
end_10:
    nop


# Problem 11: Find largest of 3 numbers.
main_11:
    # Setup numbers for program
    addi t0, x0, 9  # a = 9
    addi t1, x0, 4  # b = 4
    addi t2, x0, 6  # c = 6
    add t4, x0, t0  # smallest_found = a = 9
    bgt t4, t1, agtb # if(a > b), goto agtb
    add t4, x0, t1  # else smallest_found = b
agtb:
    bgt t4, t2, bgtc # if(smallest_found > c), goto bgtc
    add t4, x0, t2  # else smallest_found = c
bgtc:
    nop # t4 has the largest value found in the given set


# Problem 12: Find the smallest of 3 numbers.
main_12:
    # Setup numbers for program
    addi t0, x0, 9  # a = 9
    addi t1, x0, 4  # b = 4
    addi t2, x0, 6  # c = 6
    add t4, x0, t0  # smallest_found = a = 9
    blt t4, t1, altb # if(a < b), goto altb
    add t4, x0, t1  # else smallest_found = b
altb:
    blt t4, t2, bltc # if(smallest_found < c), goto bltc
    add t4, x0, t2  # else smallest_found = c
bltc:
    nop # t4 has the smallest value found in the given set


# Problem 13: Install RISCV extension and run a program.
main_13:
    # Required to get the assignment to work.
    nop


# Problem 14: Perform binary search on the array 1, 4, 8, 10, 24
# TODO: Finish this
# t0 = &ax
# t1 = low = 0
# t2 = high = len(ax)
# t3 = mid = (high + low) / 2
# t4 = ax_offset = &ax + 4(mid)
# t5 = value = ?
# t6 = ax[n]
main_14:
    la t0, ax       # Store pointer to ax[0] in t0
    addi t1, x0, 0  # low = 0
    addi t2, x0, 5  # high = size_of(ax)
    addi t5, x0, 10 # value = 10
setup_array_14:
    # ax[0] = 2
    addi t4, x0, 2
    sw t4, 0(t0)
    # ax[1] = 4
    addi t4, x0, 4
    sw t4, 4(t0)
    # ax[2] = 8
    addi t4, x0, 8
    sw t4, 8(t0)
    # ax[3] = 10
    addi t4, x0, 10
    sw t4, 12(t0)
    # ax[4] = 24
    addi t4, x0, 24
    sw t4, 16(t0)
binary_search:
    # mid = low + (high - low) / 2
    sub t3, t2, t1 # temp0 = high - low
    srli t3, t3, 1 # temp1 = temp0 / 2div
    add t3, t3, t1 # mid = low + temp1
    # Turn mid into an offset of ax[0]
    slli t3, t3, 2
    add t6, t0, t3 # Gets &ax[mid]
    lw t4, 0(t6)
    # if(ax[mid] > value)
    bgt t4, t5, axm_gt
    # if(ax[mid] < value)
    blt t4, t5, axm_lt
    # if(ax[mid] == value)
    j end_14
axm_gt:
    addi t1, t3, 1
    j binary_search
axm_lt:
    addi t2, t3, -1
    j binary_search
end_14:
    nop

# Problem 15: Describe registers x0-x31
main_15:
    #  x0: zero; Constant 0
    #  x1: ra; Return address
    #  x2: sp; Stack pointer
    #  x3: gp; Global pointer
    #  x4: tp; Thread pointer
    #  x5: t0; Temporary register
    #  x6: t1; Temporary register
    #  x7: t2; Temporary register
    #  x8: s0; Saved register, frame pointer
    #  x9: s1; Saved register
    # x10: a0; Function argument, return value 0
    # x11: a1; Function argument, return value 1
    # x12: a2; Function argument
    # x13: a3; Function argument
    # x14: a4; Function argument
    # x15: a5; Function argument
    # x16: a6; Function argument
    # x17: a7; Function argument
    # x18: s2; Saved register
    # x19: s3; Saved register
    # x20: s4; Saved register
    # x21: s5; Saved register
    # x22: s6; Saved register
    # x23: s7; Saved register
    # x24: s8; Saved register
    # x25: s9; Saved register
    # x26: s10; Saved register
    # x27: s11; Saved register
    # x28: t3; Temporary register
    # x29: t4; Temporary register
    # x30: t5; Temporary register
    # x31: t6; Temporary register
end_15:
    nop


# Problem 16: Describe each section in RISC-V and write a program that uses them
main_16:
# .data The data section containing global program variables
# .text The code portion of the program containing instructions
end_16:
    nop


# Problem 17: Program that uses `ecall`
main_17:
    addi a0, x0, 1      # Specify printing int
    addi a1, x0, 100    # Load 100 into stdout buffer
    ecall               # print(100)
end_17:
    nop # Pause here to allow for debugging

# Problem 18: Perform AND, OR, and XOR
#
main_18:
    addi t0, x0, 512  # a = 512
    addi t1, x0, 1024 # b = 1024
and_18:
    and t2, t0, t1          # c = a & b
or_18:
    or t3, t0, t1           # d = a | b
xor_18:
    xor t4, t0, t1          # e = a ^ b
end_18:
    nop # Pause here to allow for debugging


# Problem 19: Print numbers 1-10
# for(int i = 1; i <= 10; i++)
#   print(i)
main_19:
    addi t0, x0, 1      # int i = 1
    addi t1, x1, 10     # LOOP_LIMIT = 10
loop_start_19:
    addi a0, x0, 1      # Print int to output
    add a1, x0, t0      # Load int to stdout
    ecall               # Call print
    addi t0, t0, 1      # i++
    ble t0, t1, loop_start_19 # if i <= LOOP_LIMIT, continue
end_19:
    nop # Pause here to allow for debugging


# Problem 20: First 5 even and odd numbers.
# for(int i = 0; i < 10; i+=2)
#   print(i)
# for(int i = 1; i < 10; i+=2)
#   print(i)
main_20:
    addi t0, x0, 0      # int i = 0
    addi t1, x0, 10     # LOOP_LIMIT = 10
    addi a0, x0, 1      # Indicate integer as output
even_loop_start_20:
    add a1, x0, t0      # Set value to be printed
    ecall               # Call print
    addi t0, t0, 2      # i+=2
    blt t0, t1, even_loop_start_20 # if i < 10, continue
    addi t0, x0, 1      # int i = 1
odd_loop_start_20:
    add a1, x0, t0
    ecall
    addi t0, t0, 2
    blt t0, t1, odd_loop_start_20 # if i < 10, continue
end_20:
    nop # Pause here to allow for debugging

terminate_program:
    # exit(0)
    addi a0, x0, 10
    ecall

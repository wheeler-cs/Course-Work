# Addition Exercise
add:
    li t0, 10       # t0 = 10
    li t1, 12       # t1 = 12
    add t2, t0, t1  # t2 = t0 + t1

# Subtraction Exercise
sub:
    li t0, 8        # t0 = 8
    li t1, 4        # t1 = 4
    sub t2, t0, t1  # t2 = t0 - t1

# Multiplication Exercise
# int product = 0,
#     multiplicand = t0;
# for(int multiplier = t1; multiplier > 0; multiplier--)
#     product += multiplicand;
#
mult: # Implements mult t2, t0, t1
# int product, multiplicand, multiplier;
    li t0, 6            # t0 = 2, multiplicand
    li t1, 5            # t1 = 4, multiplier
    li t2, 0            # t2 = 0, product
    beqz t1, end_mult   # Don't bother with loop if t1 is 0
mult_start:
    add t2, t2, t0      # product += multiplicand
    addi t1, t1, -1     # multiplier--
    bnez t1, mult_start # Goto `mult_start` if multiplier != 0 (loop is not done yet)
end_mult:
    nop # Done

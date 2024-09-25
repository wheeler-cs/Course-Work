.data
    num_a: .word 1
    num_b: .word 2
    num_c: .word 3
    product: .word 0

.text
mult_3:
    la t0, num_a    # t0 = &num_a
    lw t1, 0(t0)    # t1 = *num_a
    la t0, num_b    # t0 = &num_b
    lw t2, 0(t0)    # t2 = *num_b
    mul t3, t2, t1  # t3 = t2 * t1
    la t0, num_c    # t0 = &num_c
    lw t1, 0(t0)    # t1 = *num_c
    mul t3, t3, t1  # t3 *= t1
    la t0, product  # t0 = &product
    sw t3, 0(t0)    # *product = t3
    nop             # PAUSE FOR DEBUG

# for(i = 10; i > 0; i--)
#   print(i)
for_loop:
    addi t0, x0, 10     # i = 10
    addi t1, x0, 1      # i > 0
    addi a0, x0, 1      # Tell stdout to expect int
loop_start:
    blt t0, t1, loop_end # if (i < 1) end loop
    add a1, x0, t0     # Buffer i to stdout
    ecall               # printf("%u", i)
    addi t0, t0, -1     # i--
    j loop_start        # Restart loop
loop_end:
    nop                 # PAUSE FOR DEBUG

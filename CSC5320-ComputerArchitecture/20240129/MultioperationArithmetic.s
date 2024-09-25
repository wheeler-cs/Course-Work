# a = b + c + d - e
multi_add:
    li t1, 5        # b = 5
    li t2, 6        # c = 6
    add t0, t1, t2  # a = b + c
    li t1, 11       # d = 11
    add t0, t0, t1  # a += d
    li t1, 14       # e = 14
    sub t0, t0, t1  # a -= 14
    nop # pause dbg to inspect reg vals

# f = (g + h) - (i + j)
paranthese_math:
add_g_h:
    li t1, 5        # g = 5
    li t2, 6        # h = 6
    add t0, t1, t2  # temp = t1 + t2
add_i_j:
    li t1, 3        # i = 3
    li t2, 2        # j = 2
    add t1, t1, t2  # temp2 = i + j
calc_f:
    sub t0, t0, t1  # f = temp - temp2
    nop # pause dbg to inspect reg vals
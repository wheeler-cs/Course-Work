# Register Usage
#   t0: year
#   t1: 4
#   t2: 100
#   t3: 400
#   t4: temp
#   t5: isLeapYear
leap_year:
    addi t0, x0, 2000   # year = 1967
    addi t1, x0, 4      # modFour = 4
    addi t2, x0, 100    # modHundred = 100
    addi t3, x0, 400    # modFourHundred = 400
mod_100: # temp = year % 100
    div t4, t0, t2      # temp = year / 100
    mul t4, t4, t2      # temp *= 100
    beq t0, t4, mod_400 # if (year % 100 != 0) goto mod_400, else goto mod_4
mod_4: # temp = year % 4
    div t4, t0, t1      # temp = year / 4
    mul t4, t4, t1      # temp *= 4
    beq t0, t4, is_leap
    j not_leap
mod_400: # temp = year % 400
    div t4, t0, t3      # temp = year / 400
    mul t4, t4, t3      # temp *= 400 
    beq t0, t4, is_leap # if (year % 400 == 0) goto is_leap, else goto not_leap
    # Fall through to not_leap
not_leap:
    addi t5, x0, 0      # isLeapYear = false
    j end_leap_year
is_leap:
    addi t5, x0, 1      # isLeapYear = true
end_leap_year:
    nop                 # Pause here for debugging

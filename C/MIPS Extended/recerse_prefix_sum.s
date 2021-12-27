reverse_prefix_sum:

    # PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra

    # use t0 to hold arr. use t1 to hold *arr
    move $t0, $a0

    lw   $t1, ($t0)
    addi $a0, 4
    beq  $t1, -1, rev_pre_end
    
    #PROLOGUE for $t0, $t1
    subu $sp, $sp, 8
    sw $t0, 8($sp)
    sw $t1, 4($sp) 
    
    jal reverse_prefix_sum

    #EPILOGUE for $t0, $t1
    lw $t0, -8($fp)
    lw $t1, -12($fp)

    addu $v0, $v0, $t1
    
    sw $v0, ($t0)

    addu $t0, $t0, 4

    j end

rev_pre_end:
    li $v0, 0

end:
    # EPILOGUE
    move $sp, $fp           # restore $sp
    lw   $ra, ($fp)         # restore saved $ra
    lw   $fp, -4($sp)       # restore saved $fp
    j    $ra                # return to kernel

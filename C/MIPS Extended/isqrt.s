isqrt:
# PROLOGUE

    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra
#main
    li $t6 2
    bgt $t6 $a0 ifblock

    #PROLOGUE a0
    subu $sp, $sp, 4 
    sw $a0 , 4($sp)

    srl $t2 $a0 2
    move $a0 $t2

    jal isqrt
    lw $a0, -8($fp)
    move $t2 $v0
    sll $t2 $t2 1 #small 

    addu $t3 $t2 1 #large 
    mul $t4 $t3 $t3 
    bgt $t4 $a0 ifblock1

    move $v0 $t3

    j endif

    ifblock:
        move $v0 $a0 
    j endif
    ifblock1:
        move $v0 $t2

endif:
# EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
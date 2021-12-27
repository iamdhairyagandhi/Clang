fibonacci:
# PROLOGUE

    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra

#main
    li $t1 0
    li $t2 1
    beq $a0 $t1 ifblock
    beq $a0 $t2 ifblock1

    subu $sp, $sp, 4
    sw $a0 ,4($sp) 

    sub $a0 $a0 1 
    jal fibonacci
    move $t3 ,$v0

    subu $sp, $sp, 4
    sw $t3 ,4($sp) 
    lw $a0, -8($fp) 
    sub $a0 $a0 2

    jal fibonacci
    
    lw $t3, -12($fp) # set $t3 to saved

    move $t4 ,$v0
    addu $t6 ,$t3 , $t4
    move $v0 $t6

    j endif 
    
    ifblock:
        li $v0 0
    j endif
    ifblock1:
        li $v0 1
    j endif

endif:
# EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
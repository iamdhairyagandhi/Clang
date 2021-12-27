reverse_prefix_sum:
# PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

# use t2 to hold arr.
   move $t2 $a0

# use t5 to hold *arr
    lw $t5 ($t2)
    li $t1 -1
    beq $t1 $t5 exit_early
    addi $t2 $t2 4

#t2 and t5
    subu $sp $sp 4
    sw $a0 4($sp)
    move $a0 $t2 

    jal reverse_prefix_sum
   
    move $t4 $v0
    lw $a0 -8($fp)
    lw $t6 ($a0)

    addu $v0 $t4 $t6
    sw $v0 ($a0)
    
    j exit 

exit_early:
    li $v0 0
    j exit

exit:
# EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
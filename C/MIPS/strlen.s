
 strlen:
 # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   # initialize counter to return
       li $v0, 0
loop:       # load value of next character
       lb $t1, ($a0)
       # check for null value
       beqz $t1, end
       # increase counter
       addi $v0, 1
       # move to next character in string
       # increase memory location
       addi $a0, 1
       # loop to get next character
       j loop
      
end:       
       li $v1, 0
       #jr $ra

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel



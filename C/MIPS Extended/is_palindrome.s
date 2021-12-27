is_palindrome:

    # PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra

    jal strlen1                  
    move $t1, $v0           
    li $t2, 2               
    move $t3, $a0          
    move $t4, $a0           
    add $t4, $t4, $t1           
    addi $t4, $t4, -1            
    div $t1, $t2               
    mflo $t1               
    
    li $t0, 0               
    
    

loop1:
    bge $t0, $t1, endloop1
    lb $t5, ($t3)             
    lb $t6, ($t4)            

   bne $t5, $t6, nopal

    addi $t3, $t3, 1
    addi $t4, $t4, -1
    addi $t0, $t0, 1
    j loop1
endloop1:
    li $v0, 1
    j end
nopal:
    li $v0, 0

end:
    # EPILOGUE
    move $sp, $fp           
    lw   $ra, ($fp)         
    lw   $fp, -4($sp)      
    j    $ra               


strlen1:
   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   # BODY
   la $t0, ($a0)             
   lb $t1, ($t0)              
   li $t2, 0                  
loop:
      beqz $t1, endloop       
      bge $t2, $a1, endloop   
      addi $t2, 1             
      lb $t1, ($t0)                                
      addi $t0, 1             
      j loop                  

endloop:   
   addi $t2, -1
   move $v0, $t2

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel


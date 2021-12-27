   .data
strbuf:
   .space 80
pass_str:
   .asciiz "pass\n"
fail_str:
   .asciiz "fail\n"

   .text
main:
   li   $sp, 0x7ffffffc    # initialize $sp

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   li   $v0, 8             # read string into strbuf
   la   $a0, strbuf        # and nul-terminate it
   li   $a1, 80            # assumes input (including \n)
   syscall                 # is less than 80 chars

   jal  strlen

   move $a0, $v0           # print_int(a0)
   li   $v0, 1
   syscall
   li   $v0, 11            # print_char(\n)
   li   $a0, 10
   syscall

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel

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



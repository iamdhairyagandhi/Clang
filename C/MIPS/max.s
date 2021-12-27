.text

#read first
addi $v0,$zero,5
syscall
add $a0,$zero,$v0


#read second
addi $v0,$zero,5
syscall
add $a1,$zero,$v0

jal max

add $a0,$zero,$v0
addi $v0,$zero,1
syscall

j exit


max:
#check if a0 greater than a1
#than jump to point
bgt $a0,$a1,point
#else a1 is bigger set it to v0
move $v0,$a1
jr $ra
point:
#a0 is bigger set it to v0
move $v0,$a0
jr $ra
exit:


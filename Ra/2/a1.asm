    .data
str:  .asciiz "Das sollte nun auf dem Stack zu sehen sein"

    .text
main:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	la $a0, str
	jal strlen
	addi $v0, $v0, 2
	add $s0, $v0, $zero
	sub $sp, $sp, $s0
	
	add $t0, $sp, $zero  # stack
	la $t1, str  # string
_loop:
	lb $t2, 0($t1)  # get char
	beqz $t2, _done
	sb $t2, 0($t0)  # store char
	addi $t0, $t0, 1
	addi $t1, $t1, 1
	j _loop
_done:
	
	add $a0, $sp, $zero
	jal printit

    li $v0, 10
    syscall

    add $sp, $sp, $s0
    lw $ra, 0($sp)
	addi $sp, $sp, 4
    jr $ra


strlen:
	add $t0, $zero, $zero
_sloop:
	lb $t1, 0($a0)
	beqz $t1, _sdone
	
	addi $a0, $a0, 1
	addi $t0, $t0, 1
	j _sloop

_sdone:	
	add $v0, $t0, $zero
	jr $ra


printit:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

    li $v0, 4
    syscall
    
	lw $ra, 0($sp)
	addi $sp, $sp, 4

    jr $ra


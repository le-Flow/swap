	.data
nl: .asciiz "\n"

	.text
main:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	# print male
	li $s0, 0
	li $s1, 10
_mloop:
	add $a0, $s0, $zero
	jal male
	
	add $a0, $v0, $zero
	li $v0, 1
	syscall
	
	addi $s0 $s0, 1
	bne $s0, $s1, _mloop
	
	# new line
	li $v0, 4
	la $a0, nl
	syscall

	# print female
	li $s0, 0
	li $s1, 10
_floop:
	add $a0, $s0, $zero
	jal female
	
	add $a0, $v0, $zero
	li $v0, 1
	syscall
	
	addi $s0 $s0, 1
	bne $s0, $s1, _floop

    li $v0, 10
    syscall
 
    lw $ra, 0($sp)
	addi $sp, $sp, 4
    jr $ra
   
   
male:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	
	add $s0, $a0, $zero
	
	beq $s0 $zero, _ml1
	subi $a0, $s0, 1
	jal male
	add $a0, $v0, $zero
	jal female
	sub $v0, $s0, $v0
	j _md

_ml1:
	li $v0, 0
_md:
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	addi $sp, $sp, 8
	
	jr $ra


female:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	
	add $s0, $a0, $zero
	
	beq $s0 $zero, _fl1
	subi $a0, $s0, 1
	jal female
	add $a0, $v0, $zero
	jal male
	sub $v0, $s0, $v0
	j _fd

_fl1:
	li $v0, 1
_fd:
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	addi $sp, $sp, 8
	
	jr $ra
   

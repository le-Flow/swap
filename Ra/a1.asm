    .data
str:  .asciiz "Das sollte nun auf dem Stack zu sehen sein"

    .text
main:
	la $a0, str
	jal strlen
	addi $v0, $v0, 2
	
	add $fp, $sp, $zero
	sub $sp, $sp, $v0
	
	add $t0, $fp, $zero  # base of frame
	la $t1, str  # str offset
	j _loopc
_loop:
	lb $t2, 0($t1)  # 
	sb $t2, 0($t0)
	addi $t0, $t0, 1
	addi $t1, $t1, 1
	subi $v0, $v0, 1

_loopc:
	bne $v0, $zero, _loop
	
	add $a0, $fp, $zero  # 0($fp) is address of string
	jal printit
	
	add $sp, $fp, $zero
    li $v0, 10
    syscall


strlen:
	add $t0, $zero, $zero
	j _sloopc
_sloop:
	addi $a0, $a0, 1
	addi $t0, $t0, 1

_sloopc:
	lb $t1, 0($a0)
	bne $t1, $zero, _sloop
	
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


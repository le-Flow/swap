
	.text
main:
	# get input integer
	li $v0, 5
	syscall
	
	add $a0, $v0, $zero
	jal magic
	
	# print result of magic
	add $a0, $v0, $zero
	li $v0, 1
	syscall
	
	li $v0, 10
    syscall
	

magic:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	li $t0, 100
	ble $a0, $t0, _l1
	# Magic(n) = n – 10 für n > 100
	subi $a0, $a0, 10
	add $v0, $a0, $zero
	j _done
_l1:
	# Magic(n) = Magic(Magic(n+11)) für n < = 100
	addi $a0, $a0, 11
	jal magic
	add $a0, $v0, $zero
	jal magic

_done:		
	lw $ra, 0($sp)
	addi $sp, $sp, 4

	jr $ra

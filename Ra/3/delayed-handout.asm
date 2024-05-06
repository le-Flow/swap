
.text 

main:
	addiu $sp, $sp, -4
	sw $ra, 0($sp)
	
	# Eingabe
	li $v0, 5
	syscall
	
	# Fakultät berechnen
	add $a0, $v0, $zero
	jal factorial
	add $zero, $zero, $zero

	# Ausgabe
	add  $a0, $v0, $zero
	li $v0, 1
	syscall
	
	# Exit
	li $v0, 10
	syscall
	
	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	jr $ra


factorial:
add $t1, $zero, $zero # i = 0 in register t1
addi $v0, $zero, 1 # 1 in result
loop:
beq $t1, $a0, end
addi $t1, $t1, 1 # i++
j loop
mul $v0, $v0, $t1 # result = result * i
end:
jr $ra
add $zero, $zero, $zero










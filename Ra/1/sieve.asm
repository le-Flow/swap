    .data
sieve: .word 0 : 1000
size: .word 1000

    .text
main:
	li $s0, 2
	la $s1, size
	lw $s1, 0($s1)
	jal init_array
	
main_loop:	
	add $a0, $s0, $zero
	jal eliminate_multiples
	jal next_prime
	add $s0, $v0, $zero
	
	mulu $t1, $s0, $s0
	blt $t1, $s1, main_loop
	
	jal print_primes
	
    li $v0, 10
    syscall


init_array:
	la $t0, sieve  # address of aray
	lw $t1, size  # loop counter
	li $t2, 1  # value to put in memory address
	
array_loop:
	sw $t2, 0($t0)  # put value in array
	addiu $t0, $t0, 4  # move to next value in array
	addiu $t1, $t1, -1  # decrement loop
	bne $t1, $zero, array_loop  # check if zero is reached
	
	la $t0, sieve  # address of aray
	li $t2, 0  # new value to put in memory address
	sw $t2, 0($t0)  # put value in array
	add $t0, $t0, 4  # move to next value in array
	sw $t2, 0($t0)  # put value in array
	
	jr $ra


eliminate_multiples:
	lw $t0, size
	add $t1, $a0, $a0  # i
	la $t2, sieve
	li $t3, 0
	
	j eliminate_loop_cmp
eliminate_loop:
	mul $t5, $t1, 4
	add $t4, $t2, $t5
	sw $t3, 0($t4)

	add $t1, $t1, $a0
	
eliminate_loop_cmp:	
	blt $t1, $t0, eliminate_loop
	
	jr $ra


next_prime:
	la $t0, size
	lw $t0, 0($t0)
	la, $t1, sieve
	addiu $t2, $a0, 1
	j prime_cmp

ploop:
	mulu $t3, $t2, 4
	addu $t3, $t3, $t1
	lw $t3, 0($t3)
	beq $t3, $zero, prime_is_zero
	add $v0, $t2, $zero
	jr $ra

prime_is_zero:	
	addiu $t2, $t2, 1

prime_cmp:
	blt, $t2, $t0, ploop
	addi $v0, $zero, -1
	jr $ra


print_primes:
	la $t0, size
	lw $t0, 0($t0)
	la, $t1, sieve
	add $t2, $zero, $zero
	
	j print_cmp

print_loop:
	mulu $t3, $t2, 4
	addu $t3, $t3, $t1
	lw $t3, 0($t3)
	beq $t3, $zero, print_is_zero
	
	li, $v0, 1
	add $a0, $t2, $zero
	syscall
	
	li $v0, 11
    addi $a0, $zero, ' '
    syscall
	
print_is_zero:
	addiu $t2, $t2, 1
print_cmp:
	bne $t2, $t0 print_loop
	jr $ra

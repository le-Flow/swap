	.data
str1: .asciiz "Geben sie eine nicht-negative Zahl ein!"
str2: .asciiz "Wurzel"
f0_5: .float 0.5
f1:   .float 1.0
klein: .float 0.00001
fzero: .float 0.0

	.text
main:
	addiu $sp, $sp, -4
	sw $ra, 0($sp)
	
	# Nach Eingabe fragen
	la $a0, str1
	li $v0, 4
	syscall
	
	# Eingabe holen
	li $v0, 6
	syscall
	
	# Wurzel berechnen
	mov.s $f12, $f0
	jal naive_sqrt
	
	# Ergebnis Ausgaben
	mov.s $f12, $f0
	li $v0, 2
	syscall
	
	# Exit
	li $v0, 10
	syscall

	lw $ra, 0($sp)
	addiu $sp, $sp, 4
	jr $ra


naive_sqrt:
	l.s $f0, f1  # result
	l.s $f1, klein  # delta
	l.s $f2, f0_5  # 0.5
	l.s $f5, fzero
	
	# $f3: temp, $f4: delta
_loop:	
	div.s $f3, $f12, $f0
	add.s $f3, $f3, $f0
	mul.s $f3, $f3, $f2
	sub.s $f4, $f3, $f0
	
	c.lt.s $f5, $f4 
	bc1t _lbl1
	neg.s $f4, $f4
_lbl1:	
	mov.s $f0, $f3
	
	c.lt.s $f1, $f4
	bc1t _loop
			
	jr $ra

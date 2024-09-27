# work with an array
      .data
sieve: 	.word   0 : 1000      # "array" of 100 words to contain the the array
size: 	.word  1000          # size of sieve "array" 
      .text

main: # our main function, there is just one...
      addiu $sp, $sp, -32
      sw $s0, 0($sp)
      sw $s1, 4($sp)
      sw $s2, 8($sp)

      la   $t0, sieve       # load base address of array
      la   $t1, size        # load address of size variable: t1 is our loop counter
      lw   $t1, 0($t1)	# load size 
      add $t2, $zero, $zero # initialize t2 to 0

initloop:
     
      sw $t2, 0($t0) # store initial i value into array element
      addi $t2, $t2, 1 # increment i by one
      add $t0, $t0, 4 # move pointer into array by 1 position
      addi $t1, $t1, -1 # decrement our loop counter 
      bne $t1, $zero, initloop # we are done once loop counter reaches 0
      # now array is initialized with values from 0 to size - 1

      #print all values,
      add $s0, $zero, $zero # loop index
      la  $t0, size        # load address of size variable: 
      lw  $s1, 0($t0)	    # load size in s1
      la  $s2, sieve    # base address of array in s2
printloop:
      sll $t1, $s0, 2 # 4 * i
      add $t1, $t1, $s2  # address of sieve[i] now in t1
      lw $t1, 0($t1) # load value at seive[i]
      mul $t1, $t1, $t1 # New: Do x*x
      
      li  $v0, 1           # service 1 is print integer
      add $a0, $t1, $zero  # put the value in a0 which is where the print routine expects it 
      syscall  # print the value
      
      li $v0, 11 # print a char, sevice 11
      addi $a0, $zero, '\n' # newline char
      syscall # print the char
      
      addi $s0, $s0, 1 # increment the loop counter 
      bne $s0, $s1, printloop # continue if we have not reached i == size yet
      
  # we are done
      lw $s0, 0($sp)
      lw $s1, 4($sp)
      lw $s2, 8($sp)
      addiu $sp, $sp, 32
  
      li   $v0, 10          # system call for exit
      syscall               # we are out of here.
		

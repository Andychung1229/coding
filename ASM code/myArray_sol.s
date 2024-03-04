	.data
myArray: 			.word 36 56 8 99 54 3 2 9 54 13
myArraySize: 		.word 10
sumMsg:			.asciiz "\nThe sum is "
meanMsg:			.asciiz "\nThe mean is "
maxMsg:			.asciiz "\nThe maximum is "

	.text
	.globl main_
main_:

		jal findSum
		la $a0, sumMsg
		li $v0, 4
		syscall
		add $a0, $s2, $zero   # $s2 has the sum of the array
		li $v0, 1
		syscall
		
		jal findMean
		la $a0, meanMsg
		li $v0, 4
		syscall
		add $a0, $s2, $zero
		li $v0, 1
		syscall	
		
		jal findMax	
		la $a0, maxMsg
		li $v0, 4
		syscall
		add $a0, $t0, $zero		
		li $v0, 1
		syscall
								
		li $v0, 10
		syscall	
		
findSum:	add $t0, $zero, $zero
		la $s0, myArray
		add $t1, $t0, $s0 	  	# $t1 has the index of myArray, actually it indicates the address of the current integer
		add $t2, $zero, $zero 	# $t2 is the counter
		addi $t3, $zero, 10     # $t3 is equal to the size of myArray
loop:	beq $t2, $t3, exitLoop  # judge if have finished the whole array
		lw $s1, 0($t1)
		add $s2, $s2, $s1		# $s2 has the sum of the array
		addi $t1, $t1, 4	    # update $t1: the address of the next integer
		addi $t2, $t2, 1        # counter $t2 = $t2 + 1
		j loop		
exitLoop: 
		jr $ra

findMean: 	la $s0, myArraySize
		lw $t0, 0($s0)          # $t0: the size of the myArray
		div $s2, $t0            # $s2 = $s2 (sum） / $t0 (size)
		mflo $s2                # div: division with overflow, set LO to quotient and HI to remainder (use mfhi to access HI, mflo to access LO)
		jr $ra

findMax:	add $t0, $zero, $zero
		la $s0, myArray
		add $t1, $t0, $s0 	  	# $t1 has the index of myArray, actually it indicates the address of the current integer
		add $t2, $zero, $zero 	# $t2 is the counter
		addi $t3, $zero, 10     # $t3 is equal to the size of myArray
loop2:	beq $t2, $t3, exitLoop2
		lw $s1, 0($t1)          # $s1: the current integer
		slt $t4, $s1, $t0       # Set less than : If $s1 is less than $t0 (the current max value), then set $t4 to 1 else set $t4 to 0
		addi $t5, $zero, 1      # $t5=1
		beq $t4, $t5, skip      # if $t4=$t5=1(i.e. $s1<$t0), go to "skip"
		add $t0, $s1, $zero		# otherwise($s1>=$t0), set $t0=$s1, i.e., $t0 stores the current max value
skip:	addi $t1, $t1, 4	    # update $t1 to indicate the address of the next integer
		addi $t2, $t2, 1        # counter $t2 = $t2 + 1
		j loop2		
exitLoop2: 
		jr $ra


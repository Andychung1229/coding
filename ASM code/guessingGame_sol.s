# A program to randomly pick a lucky number (between 1 to 100) and to ask the user to guess it.  

.data
# lower and upper bounds of the lucky number
lowBound: .word 1
highBound: .word 100


# your code begins here

# define the strings for any output messages
guessMsg: .asciiz "\n\n\nThe number of guess made so far: " 
rangeMsg: .asciiz "\nThe lucky number is between "
andMsg: .asciiz " and "
inputNumMsg: .asciiz "\nEnter your guess of the number: "
correctMsg: .asciiz "\n\nYour guess is correct!\n"
errorMsg:  .asciiz "Your input is not correct, please try again!"

# your code ends here
 

.text
.globl main

main:	# use syscall of code 30 to get the current time as the number of milliseconds from Jan. 1, 1970. The returned number is in 64 bits (lower 32 bits in $a0 and higher 32 bits in $a1)
	# you don't need to know the syscall code 30 but can see the MIPS->Syscalls tab in MARS help manual for its details. 
	li $v0, 30
	syscall 

	# use syscall of code 40 to set the seed of a random number generator. The lower 32 bits of the current time is used for the seed.
	# you don't need to know the syscall code 40 but can see the MIPS->Syscalls tab in MARS help manual for its details. 
	li $v0, 40
	addi $a1, $a0, 0
	li $a0, 1
	syscall

	la $t0, lowBound
	lw $s0, 0($t0)
	la $t1, highBound
	lw $s1, 0($t1)
	li $s5, 0            # keep the number of guesses input so far

	# get the range of the bounds  
	sub $t0, $s1, $s0
	addi $t0, $t0, 1

	# use syscall of code 42 to get a random number (returned in $a0) from the range [0, $a1).
	# you don't need to know the syscall code 42 but can see the MIPS->Syscalls tab in MARS help manual for its details. 
	li $v0, 42
	li $a0, 1
	addi $a1, $t0, 0
	syscall

	add $s2, $a0, $s0   # (random number + lower bound) yields the lucky number in the specified bounds.

guessLoop: 
	# your code begins here

	# ouput the number of guesses ($s5) input so far;
	li $v0, 4
	la $a0, guessMsg
	syscall
	li $v0, 1
	addi $a0, $s5, 0
	syscall

	# output the possible range (s0 and s1) of the lucky number as the guess hint for the user;
	li $v0, 4
	la $a0, rangeMsg
	syscall
	li $v0, 1
	addi $a0, $s0, 0
	syscall
	li $v0, 4
	la $a0, andMsg
	syscall
	li $v0, 1
	addi $a0, $s1, 0
	syscall

	# ask the user to enter a guess of the lucky number;
	li $v0, 4
	la $a0, inputNumMsg
	syscall

	# read the input number and store it in $v0.
	li $v0, 5
	syscall

	# your code ends here


	addi $s5, $s5, 1

	# assuming the input number is within the range in output, update the range for the next output   
	beq $v0, $s2, correct
	
	slt $t2, $v0, $s0
	bne $t2, $zero, error
	
	slt $t3, $s1, $v0
	bne $t3, $zero, error
	
	slt $t1, $v0, $s2
	bne $t1, $zero, updateLow  # input number ($v0) less than lucky number
	addi $s1, $v0, 0           # input number ($v0) greater than lucky number, update upper bound
	j guessLoop

error: 
	li $v0, 4
	la $a0, errorMsg
	syscall
	j guessLoop

updateLow:
	addi $s0, $v0, 0  # update lower bound
	j guessLoop

correct: 
	# your code begins here
	
	# output the message that the user's guess is correct.
	li $v0, 4
	la $a0, correctMsg
	syscall

	# your code ends here

li $v0, 10
syscall
	  

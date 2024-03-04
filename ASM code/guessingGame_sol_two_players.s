# A program to randomly pick a lucky number (between 1 to 100) and to ask the user to guess it.  

.data
# lower and upper bounds of the lucky number
lowBound: .word 1
highBound: .word 100

# define the strings for any output messages
guessMsg: .asciiz "\n\n\nThe number of guess made so far: " 
rangeMsg: .asciiz "\nThe lucky number is between "
andMsg: .asciiz " and "
playerMsg: .asciiz "\nPlayer "
inputNumMsg: .asciiz ", please enter your guess of the number: "
correctMsg: .asciiz ", your guess is correct!\n"
errorMsg:  .asciiz "Your input is not correct, please try again!"
 

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

	la $t0, lowBound     # Load Address: Set $t0 to label's address
	lw $s0, 0($t0)       # Load Word: Set $s0 to contents of effective memory word address (here, 0 means the offset)
	                     # can also use one instruction: lw $s0, lowBound

	la $t1, highBound
	lw $s1, 0($t1)
	li $s5, 0            # s5: keep the number of guesses input so far (how many times you have tried)
	li $s3, 1            # s3: track the id of player; here, initialized as 11
	                     # s0: Lowerbound of the SECRET number;  
						 # s1: Upperbound of the SECRET number;

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
	                    # i.e. hence the range of the SECRET number is [1, 100]
						# $s2 stores the Secret (lucky) number

guessLoop:
	# ouput the number of guesses ($s5) input so far;
	li $v0, 4   # syscall of code 4: print string
	la $a0, guessMsg
	syscall
	li $v0, 1   # syscall of code 1: print integer
	addi $a0, $s5, 0
	syscall

	# output the possible range (s0 and s1) of the lucky number as the guess hint for the user;
	li $v0, 4   # syscall of code 4: print string
	la $a0, rangeMsg
	syscall
	li $v0, 1   # syscall of code 1: print integer
	addi $a0, $s0, 0   # s0: Lowerbound of the SECRET number; 
	syscall
	li $v0, 4   # syscall of code 4: print string
	la $a0, andMsg
	syscall
	li $v0, 1   # syscall of code 4: print string
	addi $a0, $s1, 0   # s1: Upperbound of the SECRET number;
	syscall

	# ask the user to enter a guess of the lucky number;
    li $v0, 4   # syscall of code 4: print string
	la $a0, playerMsg  # print "Player"
	syscall

	li $v0, 1   # syscall of code 1: print integer
	addi $a0, $s3, 0   #  print ID of the current player
	syscall

	li $v0, 4   # syscall of code 4: print string
	la $a0, inputNumMsg
	syscall

	# read the input number and store it in $v0.
	li $v0, 5   # syscall of code 5: read integer, $v0 contains integer read
	syscall

	# update the number of guesses ($s5)
	addi $s5, $s5, 1

	# assuming the input number is within the range in output, update the range for the next output   
	beq $v0, $s2, correct   # Branch to statement at 'correct' if $v0(the guess) is equal to the $s2(lucky number)
	
	slt $t2, $v0, $s0      # Set less than : If $v0(the guess) is less than $s0(Lowerbound), then set $t2 to 1 else set $t2 to 0
	bne $t2, $zero, error  # Branch if not equal : Branch to statement at 'error' if $t2 != 0
	
	slt $t3, $s1, $v0      # Set less than : If $s1(Upperbound) < $v0(the guess), then set $t3 = 1 else set $t3 to 0
	bne $t3, $zero, error  # Branch if not equal : Branch to statement at 'error' if $t3 != 0
	
	slt $t1, $v0, $s2      # Set less than : If $v0(the guess) < $s2(lucky number), then set $t1 = 1 else set $t1 to 0
	bne $t1, $zero, updateLow  # if input number ($v0) less than lucky number, go to the 'updateLow' part;
	addi $s1, $v0, 0           # otherwise, input number ($v0) greater than lucky number, update upper bound ($s1).
	j updatePlayer


error: 
	li $v0, 4   # syscall of code 4: print string
	la $a0, errorMsg
	syscall
	j guessLoop

updateLow:
	addi $s0, $v0, 0  # update lower bound ($s0)
	j updatePlayer

updatePlayer:
    # change the Player
    subi $t0, $s3, 1             # $t0 = $s3 - 1
    bne $t0, $zero, Player2to1   # if $t0 != 0 (i.e. $s3 != 1), go to 'Player2to1'
    li $s3, 2                    # otherwise, change player 1 to 2
    j guessLoop

Player2to1:
    li $s3, 1    # change player 2 to 1
    j guessLoop

correct: 	
	# output the message that the user's guess is correct.
	li $v0, 4   # syscall of code 4: print string
	la $a0, playerMsg  # print "Player"
	syscall

	li $v0, 1   # syscall of code 1: print integer
	addi $a0, $s3, 0   #  print ID of the current player
	syscall

	li $v0, 4
	la $a0, correctMsg
	syscall

li $v0, 10   # code 10: terminate
syscall
	  

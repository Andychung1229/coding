# Your name:Chung Ka Wai
# Your student id:20857033
# Your email address:kwchungac@connect.ust.hk

.data
# output messages
ROW: .word 0
NUM: .word 0
win1:    .asciiz "\n\n Player 1 Wins."
win2:    .asciiz "\n\n Player 2 Wins."
A_asc: .byte 0x41
#word 0x0041
B_asc: .word 0x0042
C_asc: .word 0x0043
ROWC: .word 0x0008
ROWB: .word 0x0005
ROWA: .word 0x0003
p_rowa: .asciiz "\nROW A: "
p_rowb: .asciiz "\nROW B: "
p_rowc: .asciiz "\nROW C: "
rock: .asciiz "o"
newline: .asciiz "\n"
player1: .asciiz "Player 1, choose a row and number of rocks: "
player2: .asciiz "Player 2, choose a row and number of rocks: "
tryagain: .asciiz "\n Invalid move. Try again.\n"


.text
.globl main
# $a0, syscall use
# $t0 ROW, $t1 NUM
# $t2, use to denote palyer 1/2 turns
main:
	add $t1,$zero,$zero		# $t1 = 0
	add $t2,$zero,$zero	        # $t2 = 0, player 1 first

continue:
    	jal print_state

need_input:
    	# cout << 
    	la $a0, player1
    	beq $t2, $zero, p1_print	# if $t2 == $zero then goto p1_print
    	la $a0, player2		# 
    
p1_print:
	addi $v0, $zero, 4
	syscall

    	# Read a character from the console, player A/B in $t0
    	li $v0, 12
    	syscall
    	add $t0, $v0, $zero

    	la		$a0, ROW		# 
    	sw		$t0, 0($a0)		# 
    
    	# Read a number from the console, number of stone in $t1
	li $v0, 12
	syscall
    	add $t1,$v0,$zero
	subi $t1, $t1, 48 # $t1 = $t1 - 48 to get back the actual number, for example ASCII encoding of "1" is 49, so we will have 49-48=1 in this case
	

    	la $a0, NUM		
    	sw $t1, 0($a0)	  # store the input value to the main memory	


        #back up $t2 before calling valid_move() (newly added on 1/4)
        add $sp,$sp,-4
        sw $t2,($sp)
        
	# calls valid_move() procedure
	# valid_move() returns the result in $v0, valid :1, invalid :0;
	jal valid_move

	#restore $t2 after calling valid_move() (newly added on 1/4)
        lw $t2,($sp)
        add $sp,$sp,4
        
	bgt $v0, $zero, valid	# if $v0 > $zero then goto valid
	



		
	# cout << "try again"
	la $a0, tryagain
	addi $v0, $zero, 4
	syscall
	
	j need_input

valid:
        #this part changes the player number in $t2 from 0 to 1 or 1 to 0 for the next term
	addi	$t2, $t2, -1		# $t2 = $t2 - 1
	beq	$t2, $zero, no_plus_2	# if $t2 == $zero then goto no_plus_2
	addi	$t2, $t2, 2		# $t2 = $t2 +2

no_plus_2:
	# calls game_over() procedure to check whether the game should be ended
	# game_over() returns the result in $v0, over :1, not over :0. if over, $t2 knows who win. 0 is palyer1, 1 is player2
	jal game_over
	bgt $v0, $zero, over_print	# if $v0 > $zero then goto over_print to print end game message
	
	# newline
	la $a0, newline
	addi $v0, $zero, 4
	syscall

	j continue				# jump to continue

over_print:
	# cout << "win1"
	la $a0, win1
	beq $t2, $zero, win1_print	# if $t2 == $zero then goto win1_print
	la $a0, win2		# 
	
win1_print:
	addi $v0, $zero, 4
	syscall

	# exit the program
	exit:
	addi $v0, $zero, 10 
	syscall	

	
# $v0, over :1, not over :0. if over, $v1 knows who win. 0 is palyer1, 1 is player2
#---- region : game_over subroutine
game_over:
	lw $t0,ROWC
	bne		$t0, $zero, not_over	# if $t0 != $zero then goto not_over
	lw $t0,ROWB
	bne		$t0, $zero, not_over	# if $t0 != $zero then goto not_over
	lw $t0,ROWA
	bne		$t0, $zero, not_over	# if $t0 != $zero then goto not_over
	li $v0,1
	jr $ra
	
not_over:
	li $v0,0	
	jr $ra
#---- endregion

#valid_move() procedure
#This function gets two argument: row number for removing the stone, 
#and the number of stones to be removed in the variable ROW and NUM in the main memory
#ROW is assumed to be A, B or C
#NUM is assumed to be 1,2,...,9
#It illustrate argument passing through the memory. The required arguments:
# 1) ROW is in memory under the label ROW
# 2) NUM is in memory under the lable NUM
#This function returns the result in $v0,
#$v0=1, the user move is valid
#$v0=0, the user move is invalid 
#<Preserve registers according to the MIPS register convention on slide 76 of the ISA note set>
#---- region : valid_move subroutine
valid_move:
	#TODO Below
	addi $sp,$sp,-24
	
	##lw $s1,8($sp)
	lw $s2,($sp)
	lw $s3,4($sp)
	lw $s4,8($sp)
	lw $s5,12($sp)
	lw $s6,16($sp)
	lw $s7,20($sp)
	
	#lw $s0,NUM
	#lw $s1,ROW
	lw $s2,A_asc
	lw $s3,B_asc
	lw $s4,C_asc
	lw $s5,ROWA
	lw $s6,ROWB
	lw $s7,ROWC
	
	
	slti $t6,$t1,1
	beq $t6,1,Return_0
	
	slti $t6,$t1,10
	beq $t6,0,Return_0
	
	bne $t0,$s2,ROWB_COMPARE
	beq $t1,$s5,Next
	slt $t6,$t1,$s5
	beq $t6,0,Return_0
Next:
	sub $s5,$s5,$t1
	sw $s5,ROWA
	j Return
ROWB_COMPARE:	
	bne  $t0,$s3,ROWC_COMPARE
	beq $t1,$s6,Next1
	slt $t6,$t1,$s6
	beq $t6,0,Return_0
Next1:
	sub $s6,$s6,$t1
	sw $s6,ROWB
	j Return
ROWC_COMPARE:
	bne  $t0,$s4,Return_0
	
	beq $t1,$s7,Next2
	slt $t6,$t1,$s7
	beq $t6,0,Return_0
Next2:
	sub $s7,$s7,$t1
	sw $s7,ROWC
	j Return
	
	
	
Return:
	li $v0,1
	j Exit
Return_0:
	li $v0,0
Exit:
	
	
	#sw $s0,4($sp)
	#sw $s1,8($sp)
	sw $s2,($sp)
	sw $s3,4($sp)
	sw $s4,8($sp)
	sw $s5,12($sp)
	sw $s6,16($sp)
	sw $s7,20($sp)
	addi $sp,$sp,24
	#TODO Above
	jr $ra
#---- endregion

#---- region : print_state subroutine
print_state:
        #backup $ra to stack
	addi $sp,$sp,-4 
	sw $ra,($sp)
	
	# cout << "p_rowa"
	la $a0, p_rowa
	addi $v0, $zero, 4
	syscall

	#
	lw $t8, ROWA		 
	jal print_rocks

	# cout << "p_rowb"
	la $a0, p_rowb
	addi $v0, $zero, 4
	syscall

	#
	lw $t8, ROWB		
	jal print_rocks

	# cout << "p_rowc"
	la $a0, p_rowc
	addi $v0, $zero, 4
	syscall
	
	#
	lw $t8, ROWC	 
	jal print_rocks

	la $a0, newline
	addi $v0, $zero, 4
	syscall

	#restore $ra
	lw $ra,($sp)
	addi $sp,$sp,4
	jr $ra
#---- endregion

#---- region : print_rocks subroutine
print_rocks:
	li $t9,0
	
loop_print_rock:
	beq $t9,$t8,end_print_rocks
	la $a0, rock
	addi $v0, $zero, 4
	syscall
	addi $t9,$t9,1
	j loop_print_rock
	
end_print_rocks:
	jr $ra

#---- endregion


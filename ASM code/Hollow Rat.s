# Print a RAT with stars with nested for loop
# You can modify the code to print fat RAT, upside-down RAT and hollow RAT, have a try

#------- Data Segment ----------
.data
msg1: .asciiz "Input the size of RAT: "
star: .asciiz "*"
newLine: .asciiz "\n"
blank: .asciiz " "

RAT: .asciiz "RAT:\n"
fatRAT: .asciiz "Fat RAT:\n"
hollowRAT: .asciiz "Hollow RAT:\n"


#------- Text Segment ----------
.text
.globl main

# $s0: size of RAT
# top row (row 0): 1 star
# 2nd row （row 1）: 2 stars
# row i: i+1 stars

# $t0: i, $t1: j
# for (int i = 0; i < size; i++) {
#    for (int j = 0; j <= i; j++)
#        cout << "*";
#    cout << endl;
# }

main: 
	la $a0, msg1 		# print msg
	li $v0, 4
	syscall
	
	li $v0, 5 		# read int
	syscall 		# the int is in $v0
	move $s0, $v0 		# pseudo instruction

	la $a0, hollowRAT 		# print msg
	li $v0, 4
	syscall
	
	li $t0, 0		# i = 0
	subi $s0, $s0, 1
outer_loop: 
	slt $t2,$t0,$s0		# if (i<size) loop
	beq $t2, 0, lastline
	
	move $t1, $0
inner_loop: 
	slt $t2, $t0, $t1	# if (j <= i) is equivalent to if !(i < j)
	bne $t2, $0, print_enter
	slt $t2, $zero, $t1
	beq $t2, $0, print_star
	slt $t2, $t1, $t0
	beq $t2, $0, print_star

	la $a0, blank		# draw a blank
	li $v0, 4
	syscall
	j increment_j
print_star:
	la $a0, star		# draw a star
	li $v0, 4
	syscall
increment_j: 
	addi $t1, $t1, 1
	j inner_loop	
	
print_enter:
	la $a0, newLine		# print enter
	li $v0, 4
	syscall
		
increment_i:
	addi $t0, $t0, 1
	j outer_loop

lastline:
	add $t0, $s0, $zero 
	move $t1, $0
	
inner_loop2: 
	slt $t2, $t0, $t1	# if (j <= i) is equivalent to if !(i < j)
	bne $t2, $0, exit
	
	
	la $a0, star		# draw a star
	li $v0, 4
	syscall
	addi $t1, $t1, 1
	j inner_loop2	


exit:
	li $v0, 10
	syscall
	






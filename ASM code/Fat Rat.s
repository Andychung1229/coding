# Print a RAT with stars with nested for loop
# You can modify the code to print fat RAT, upside-down RAT and hollow RAT, have a try

#------- Data Segment ----------
.data
msg1: .asciiz "Input the size of RAT: "
star: .asciiz "*"
newLine: .asciiz "\n"

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

	la $a0, fatRAT 		# print msg
	li $v0, 4
	syscall
	
	li $t0, 0		# i = 0
outer_loop: 
	slt $t2,$t0,$s0		# if (i<size) loop
	beq $t2, 0, exit
	
	move $t1, $0
inner_loop: 
	slt $t2, $t0, $t1	# if (j <= i) is equivalent to if !(i < j)
	bne $t2, $0, print_enter
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
	addi $t0, $t0, 2
	j outer_loop

exit:
	li $v0, 10
	syscall
	






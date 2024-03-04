# Your name:Chung Ka Wai
# Your student id:20857033
# Your email address:kwchungac@connect.ust.hk

.data
# output messages
PleaseMsgA1: .asciiz "Please enter the size of your matrix A:\n"
PleaseMsgA2: .asciiz "Please enter integers in array A[] one by one:\n"
PleaseMsgF1: .asciiz "Please enter the size of your matrix F:\n"
PleaseMsgF2: .asciiz "Please enter integers in array F[] one by one:\n"
MatrixMsgA1: 	.asciiz "A["
MatrixMsgF1: 	.asciiz "F["
MatrixMsgB1: 	.asciiz "B["
MatrixMsg2: 	.asciiz "]["
MatrixMsg3: 	.asciiz "]: "

OutMsg1:	.asciiz "After convolution:\n"
space: .asciiz "\t"
newline: .asciiz "\n"

A: .word 0:100
F: .word 0:50
B: .word 0:100
A_size: .word 0
F_size: .word 0
B_size: .word 0

.text
.globl main

main:
    # $s0 :base addr of A; 
    # $s1 :size of A[];
    # $s2 :base addr of F; 
    # $s3 :size of F[];
    # $s4 :base addr of B; 
    # $s5 :size of B[];
    
    la $s0,A # $s0 :base addr of A;
    la $s2,F # $s2 :base addr of F;
    la $s4,B # $s4 :base addr of B;
    
#---- region : message befor input matrix A
    # cout << "Please enter the size of your matrix A:" << endl;
    la $a0, PleaseMsgA1
	addi $v0, $zero, 4
	syscall

	# cin >> A_size; use $s1
	li $v0, 5
	syscall
	add $s1,$v0,$zero

    # cout << "Please enter integers in array A[] one by one:" << endl;
	la $a0, PleaseMsgA2
	addi $v0, $zero, 4
	syscall
#---- endregion

#---- region : input A[i][j], for loop, use $t0,t1, save in $s0, size is $s1
	li $t0,0
	
A_outer_for_Loop:
	beq $t0,$s1,A_exit_outer_for_Loop
        add $t1,$zero,$zero
        
A_inner_for_Loop:
	beq $t1,$s1,A_exit_inner_for_Loop	
	# cout << "A["
	la $a0, MatrixMsgA1
	addi $v0, $zero, 4
	syscall
	
	# print index
	add $a0,$t0,$zero
	addi $v0, $zero, 1
	syscall
	
	# cout << "]["
	la $a0, MatrixMsg2
	addi $v0, $zero, 4
	syscall

	# print index
	add $a0,$t1,$zero
	addi $v0, $zero, 1
	syscall
	
	# cout << "]: "
	la $a0, MatrixMsg3
	addi $v0, $zero, 4
	syscall
	
	# read user input in $v0
	li $v0, 5
	syscall
	add $v1,$v0,$zero
	
   	#### need multiply
	add $a0,$t0,$zero
	add $a1,$s1,$zero
	
       	jal multiply      #calculate  A_size*i
        
	add $t3,$v0,$zero #A_size*i in $t3
	add $t3,$t3,$t1   #idx = A_size*i + j

	sll $t3,$t3,2     # calculate the offset for the element A[idx] (i.e. idx*4)
	add $t3,$t3,$s0   # calculate the addr of A[idx], $t3 = i*4 + base of A in $s0
	sw $v1, 0($t3)    # A[idx] = $v0 (user input from the previous syscall)

    	addi $t1,$t1,1
    	j A_inner_for_Loop
    	
A_exit_inner_for_Loop:
	addi $t0,$t0,1
	j A_outer_for_Loop
	
A_exit_outer_for_Loop:
#---- endregion

#---- region : message befor input matrix F
    # cout << "Please enter the size of your matrix F:" << endl;
    	la $a0, PleaseMsgF1
	addi $v0, $zero, 4
	syscall

	# cin >> F_size; use $s3
	li $v0, 5
	syscall
	add $s3,$v0,$zero

    # cout << "Please enter integers in array F[] one by one:" << endl;
	la $a0, PleaseMsgF2
	addi $v0, $zero, 4
	syscall
#---- endregion

#---- region : input F[i][j], for loop, use $t0,t1, save in $s2, size is $s3
	li $t0,0
	
F_outer_for_Loop:
	beq $t0,$s3,F_exit_outer_for_Loop
    	add $t1,$zero,$zero
    	
F_inner_for_Loop:
	beq $t1,$s3,F_exit_inner_for_Loop
	
	# cout << "F["
	la $a0, MatrixMsgF1
	addi $v0, $zero, 4
	syscall
	
	# print index
	add $a0,$t0,$zero
	addi $v0, $zero, 1
	syscall
	
	# cout << "]["
	la $a0, MatrixMsg2
	addi $v0, $zero, 4
	syscall

	# print index
	add $a0,$t1,$zero
	addi $v0, $zero, 1
	syscall
	
	# cout << "]: "
	la $a0, MatrixMsg3
	addi $v0, $zero, 4
	syscall
	
	# read user input in $v0
	li $v0, 5
	syscall
	add $v1,$v0,$zero
	
    	#### need multiply
	add $a0,$t0,$zero
	add $a1,$s3,$zero
	
	#addi $sp,$sp,-4 #back up $ra
	#sw $ra,($sp)
	jal multiply
	#lw $ra,($sp) #restore $ra
	#addi $sp,$sp,4

	add $t3,$v0,$zero # idx=$t3= F_size*i 
	add $t3,$t3,$t1    # idx=$t3= F_size*i+j

	sll $t3,$t3,2     # calculate the offset of F[idx] (i.e. idx*4)
	add $t3,$t3,$s2   # calculate for the addr of F[idx], $t3 = i*4 + base of F in $s2, 
	sw $v1, 0($t3)    # F[idx] = $v1 (the input from the previous syscall 

   	addi $t1,$t1,1
    	j F_inner_for_Loop
    	
F_exit_inner_for_Loop:
	addi $t0,$t0,1
	j F_outer_for_Loop
	
F_exit_outer_for_Loop:
#---- endregion

#---- region : prepare for and then call TwoDimensionConv() subroutine
    	sub $s5,$s1,$s3   
    	addi $s5,$s5,1      #$s5=B_size=A_size-F_size-1
    
    	add $a0,$s1,$zero   #Put A_size into $a0 for TwoDimensionConv()   
    	add $a1,$s3,$zero   #Put F_size into $a1 for TwoDimensionConv()   
    	
        #There is no need to provide base addresses of A[], F[], and B[] to TwoDimensionConv
        #as they are in $s0,$s2,$s4
    	jal TwoDimensionConv
#---- endregion

#---- region : message befor output matrix B
    	# cout << "After convolution:" << endl;
    	la $a0, OutMsg1
    	addi $v0, $zero, 4
    	syscall
#---- endregion

#---- region : ouput B[i][j], for loop, use $t0,t1, saveed in $s4, size is $s5
    	li $t0,0

B_outer_for_Loop:
	beq $t0,$s5,B_exit_outer_for_Loop    
    	li $t1,0
    	
B_inner_for_Loop:

	beq $t1,$s5,B_exit_inner_for_Loop
	
	# cout << "B["
	la $a0, MatrixMsgB1
	addi $v0, $zero, 4
	syscall
	
	# print index
	add $a0,$t0,$zero
	addi $v0, $zero, 1
	syscall
	
	# cout << "]["
	la $a0, MatrixMsg2
	addi $v0, $zero, 4
	syscall

	# print index
	add $a0,$t1,$zero
	addi $v0, $zero, 1
	syscall
	
	# cout << "]: "
	la $a0, MatrixMsg3
	addi $v0, $zero, 4
	syscall
	
    	#### need multiply
	add $a0,$t0,$zero
	add $a1,$s5,$zero
	
       	jal multiply
    
	add $t3,$v0,$zero
	add $t3,$t3,$t1

	sll $t3,$t3,2
	add $t3,$t3,$s4 # $t3 = i*4 + base of B in $s4, addr of B[idx]
    	lw $a0, 0($t3)
	addi $v0, $zero, 1
	syscall 
	
	la $a0, space
	addi $v0, $zero, 4
	syscall # cout << B[idx] << ", ";

    	addi $t1,$t1,1
	j B_inner_for_Loop
	
B_exit_inner_for_Loop:
	la $a0, newline
	addi $v0, $zero, 4
	syscall # cout << endl;

	addi $t0,$t0,1
	j B_outer_for_Loop

B_exit_outer_for_Loop:
#---- endregion

#---- region : end this program
	exit:
	addi $v0, $zero, 10 
	syscall
#---- endregion

#---- region : subroutine of multipy(), use $t4 but use stack to save%restore
#this multiply procedure will modify $t4 and $v0
multiply:
	li $t4,0
	li $v0,0

	enter_m_for:
	beq $t4,$a1,exit_m_for
	add $v0,$v0,$a0
	addi $t4,$t4,1
	j enter_m_for
	exit_m_for:
	    	
	jr $ra
#---- endregion


#The TwoDimensionConv() procedure
#Input argments: 
#$a0 = A_size
#$a1 = F_size
#Different than the C++ function, the following arguments are in the saved registers (i.e. $s0 - $s5) and are not passed
#This function can directly read the values from the saved registers.
# assume base addr of A[] already in $s0, so do not need to pass
# assume base addr of B[] already in $s4, so do not need to pass
# assume base addr of F[] already in $s2, so do not need to pass
# assume B_size already in $s5, so do not need to pass
# If you decide to change the saved register values in this function, then remember to preserve registers according to the MIPS register convention on slide 76 of the ISA note set
# In general, preserve registers accoding to slide 76 of the ISA note set
#output: none
#effect: calculates and stores all the elements of the output matrix B
##<important 1>:
#this function needs to call the ConvForElement() for calculating B_ij, refer to the C++ program for the details
#the convForElement() procdure will change the following registers:
#$t2, $t3, $t6, $t7, $t8, $t9, $v0
#If you need to use these registers in the implementation of this procedure
#make sure you 1) backup them before calling convForElement , 2) restore them right after calling convForElement()
#make sure the $sp to be the same before and after doing 1) and 2) above (i.e. allocate n bytes, delocate n bytes)
##<important 2>:
#this function also calls the multiply() procedure, and multiply() changes the following register:
#$t4, $v0
#If you need to use these registers in the implementation of this procedure
#make sure you 1) backup them before calling multiply() , 2) restore them right after calling multiply()
#make sure the $sp to be the same before and after doing 1) and 2) above (i.e. allocate n bytes, delocate n bytes)
##<important 3>:
#this function will make function calls, make sure you backup $ra at the beginning of the function and restore it before returning
TwoDimensionConv:
    #TODO Below
    	addi $sp,$sp,-4
    	sw $ra,($sp)
   	li $t0,0 #local_sum=0
   	li $t1,0 #B_index=0;
    
    
    
    	li $t2,0# B_I
    	li $t4,0
    	sub $t4,$a0,$a1
    	addi $t4,$t4,1# A_size-F_size+1
first_loop:
	beq $t2,$t4,Exit_i
	li $t3,0#b_j
second_loop:
	beq $t3,$t4,Exit_j
	
	
	#multi
	addi $sp,$sp,-16
	sw $a0,($sp)
	sw $a1,4($sp)
	sw $t4,8($sp)
	sw $v0,12($sp)
	
	add $a0,$s5,$zero
	add $a1,$t2,$zero
	jal multiply
	
	add $t1,$v0,$zero
	add $t1,$t1,$t3#B_index= mult +B_j
	
	lw $a0,($sp)
	lw $a1,4($sp)
	lw $t4,8($sp)
	lw $v0,12($sp)
	addi $sp,$sp,16 # restoring 
	
	li $t0,0 #local_sum=0
	#$t2, $t3, $t6, $t7, $t8, $t9, $v0 are needed to store 
	addi $sp,$sp,-44
	sw $a0,($sp)
	sw $a1,4($sp)
	sw $a2,8($sp)
	sw $a3,12($sp)
	sw $t2,16($sp)
	sw $v0,20($sp)
	sw $t3,24($sp)
	sw $t6,28($sp)
	sw $t7,32($sp)
	sw $t8,36($sp)
	sw $t9,40($sp)
	
	add $a3,$a1,$zero
	add $a2,$a0,$zero
	add $a0,$t2,$zero
	add $a1,$t3,$zero
	jal ConvForElement
	
	sll $t1,$t1,2 # get B[B_index]
	add $t1,$t1,$s4
	sw $v0,($t1)
	
	
	lw $a0,($sp)
	lw $a1,4($sp)
	lw $a2,8($sp)
	lw $a3,12($sp)
	lw $t2,16($sp)
	lw $v0,20($sp)
	lw $t3,24($sp)
	lw $t6,28($sp)
	lw $t7,32($sp)
	lw $t8,36($sp)
	lw $t9,40($sp)
	addi $sp,$sp,44
	
Jump_j_loop:
	addi $t3,$t3,1
	j second_loop
Exit_j:
	addi $t2,$t2,1
	j first_loop
	
Exit_i:
	lw $ra,($sp)
        add $sp,$sp,4
    	
    #TODO Above
    jr $ra



#The ConvForElement() procedure
#input arguments:
# $a0: B_i
# $a1: B_j
# $a2: A_size
# $a3: F_size
# assume base addr of A[] already in $s0, so do not need to pass
# assume base addr of F[] already in $s2, so do not need to pass
#return value:
# $v0: local_sum (calculated value for B_ij, refer to the C++ program)
## 
# registers used in the procedure:
# $t2: F_i
# $t3: F_j
# $t6: local_sum
# $t7: for holding the addresses of A[A_idx], F[F_idx]  
# $t8: F_idx; also content of F[F_idx]
# $t9: A_idx; also content of A[A_idx]
# 
ConvForElement:
	#backup $ra
	addi $sp,$sp,-4
	sw $ra,($sp)
	
	#put 0 into $t6
	add $t6,$zero,$zero
	
    	# F_i loop starts
    	li $t2,0 #f_idx=0
F_i_for_Loop:

    	beq $t2,$a3,F_i_exit_for_Loop
    
   	 # F_j loop starts
    	li $t3,0
F_j_for_Loop:
    	beq $t3,$a3,F_j_exit_for_Loop
    
    	## below calculates F_idx in $t8, F_idx=F_size*F_i +F_j
    	# need multiply
        addi $sp,$sp,-8 #allocate 2 words
        sw $a0,($sp)     #back up $a0
        sw $a1,4($sp)    #back up $a1

	add $a0,$t2,$zero #$a0=F_i
	add $a1,$a3,$zero #$a1=F_Size
    
	jal multiply     #calculate F_size*F_i

        lw $a1,4($sp)    #restore $a1
        lw $a0,0($sp)    #restore $a0
        addi $sp,$sp,8   #delocate 2 words    
        	
	add $t8,$v0,$zero #$t8=F_size*F_i
	add $t8,$t8,$t3   #$t8=F_size*F_i + F_j
   	## above calculates F_idx in $t8, F_idx=F_size*F_i + F_j

        
    	## below calculates A_idx in $t9, A_idx=A_size*(B_i+F_i)+B_j+F_j
       	add $t9,$a0,$t2       #$t9=B_i+F_i
       
    	# need multiply    
        addi $sp,$sp,-8 #allocate 2 words
        sw $a0,($sp)     #back up $a0
        sw $a1,4($sp)    #back up $a1
            
	add $a0,$t9,$zero 
	add $a1,$a2,$zero
	
	jal multiply      #calculate A_size*(B_i+F_i)
	
        lw $a1,4($sp)    #restore $a1
        lw $a0,0($sp)    #restore $a0
        addi $sp,$sp,8   #delocate 2 words
        
	add $t9,$v0,$zero#$t9=A_size*(B_i+F_i)
        add $t9,$t9,$a1  #$t9=A_size*(B_i+F_i)+B_j
        add $t9,$t9,$t3  #$t9=A_size*(B_i+F_i)+B_j+F_j
    	## the above calculates A_idx in $t9, A_idx=A_size*(B_i+F_i)+B_j+F_j


    	sll $t7,$t8,2     # calculate the offset  $t7=F_idx*4
    	add $t7,$t7,$s2   # $t7 = F_idx*4 + base of F 
    	lw $t8, 0($t7)    # $t8 = F[F_idx]
  
    	sll $t7,$t9,2   # calculate the offset $t7=A_idx*4
    	add $t7,$t7,$s0 # $t7 = A_idx*4 + base of A
    	lw $t9, 0($t7)  # $t9 = A[A_idx]

    	bltz $t8, do_sub    # if F[F_idx]<0 then local_sum=local_sum-A[A_idx]
    	bgtz $t8, do_add    # if F[F_idx]>0 then local_sum=local_sum+A[A_idx]
    	j ctn_with_F_i_Loop
    
do_sub:
    	sub	$t6, $t6, $t9      # $t6 is local_sum, local_sum = local_sum - A[A_idx]
    	j ctn_with_F_i_Loop
    
do_add:
    	add	$t6, $t6, $t9       # $t6 is local_sum, local_sum = local_sum + A[A_idx]
    	j ctn_with_F_i_Loop


ctn_with_F_i_Loop:
       	addi $t3,$t3,1 #increment F_j
    	j F_j_for_Loop #start another iteration of F_j loop
    	
F_j_exit_for_Loop:
    	addi $t2,$t2,1 #increment F_i
    	j F_i_for_Loop #start another iteration of F_i loop
    	
F_i_exit_for_Loop:
    	add $v0,$t6,$zero #Copy local_sum to $v0 before returning
    	
    	#restore $ra
        lw $ra,($sp)
        add $sp,$sp,4
    	jr $ra

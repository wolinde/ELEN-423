# ******************************************************************
# Simple Assembly Program
# ******************************************************************
# Name:		Simple Assembly Program
# Purpose:	Show how to do simple things in assembly language.
#
# Uses print, xil_printf, loops, conditionals, etc.
# ******************************************************************

# ************************
# Equates
# ************************
.set NUM_LOOPS, 10 

# ************************
# Memory Sections
# ************************
$msgBEGIN:
	.ascii	"\r\n**** Program Begin ****\r\n\r\n\0\000"
	.text
	.align	2

$msgWithInteger:
	.ascii	"Circuits are wonderful -  %d!!!!!\r\n\0\000"
	.text
	.align	2

$msgEND:
	.ascii	"\r\n**** Program End ****\r\n\0\000"
	.text
	.align	2

# ************************
# Main Program
# ************************
.globl	main
main:

	# *************** Use print *******************
	# GOAL: print out a simple string at the beginning of the program
	# *********************************************
	# r5 will contain the address of the string to print
	# *********************************************

	# Store string in r5
	addi r5, r0, $msgBEGIN
	
	# Push r15 on stack
	addi r1, r1, -4	
	swi	r15 ,r1, 0
	
	# Call print function (return address stored in r15)
	brlid	r15, print
	nop		# Unfilled delay slot

	# Pop r15 off stack
	lwi r15, r1, 0
	addi r1, r1, 4	

	# *************** Use xil_printf in a loop *******************
	# GOAL: loop while printing out a formatted string with an integer
	# ************************************************************
	# r5 will contain the address of the string to print
	# r6 will contain the integer to print with the string
	# r19 will contain the loop counter (that decrements)
	# r20 will contain the value 1 (used to decrement by 1)
	# ************************************************************

	# Init loop counter (r19)
	addi r19, r0, NUM_LOOPS
	
	# Init register to 1
	addi r20, r0, 1
		
.globl	myLoop
myLoop:	

	# Check loop condition (if r19 = 0 then program is finished, otherwise continue)
	beqi r19, done
	nop

	# Decrement loop counter
	rsub r19, r20, r19
	
	# Set r5 to the message
	addi r5, r0, $msgWithInteger

	# Set r6 to loop counter value (number to print)
	addk r6, r19, r0

	# Push r15 on stack
	addi r1, r1, -4
	swi	 r15, r1, 0
	
	# Call print function (return address stored in r15)
	brlid	r15, xil_printf
	nop
	
	# Pop r15 off stack
	lwi r15, r1, 0
	addi r1, r1, 4	

	# Start over (loop back)
	bri myLoop
	nop

# Display a message that the program is ending	
.globl	done
done:

	# *************** Use print *******************
	# GOAL: print out a simple string at the end of the program
	# *********************************************
	# r5 will contain the address of the string to print
	# *********************************************

	# Store string in r5
	addi r5, r0, $msgEND
		
	# Push r15 on stack
	addi r1, r1, -4
	swi	r15, r1, 0
	
	# Call print function (return address stored in r15)
	brlid	r15, print
	nop		# Unfilled delay slot

	# Pop r15 off stack
	lwi r15, r1, 0
	addi r1, r1, 4	

# Infinite loop on exit
.globl endLoop
endLoop:
	bri endLoop

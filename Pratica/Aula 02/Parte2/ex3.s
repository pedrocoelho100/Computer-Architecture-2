		.equ READ_CORE_TIMER,11
 		.equ RESET_CORE_TIMER,12
 		.equ PUT_CHAR,3
 		.equ PRINT_INT,6
 		.data
 		.text
 		.globl main
main: 	li $t0,0
while: 	li $v0,READ_CORE_TIMER 	# while (1) {
 		syscall 				#
 		
 		blt $v0,40000,while 	# while(readCoreTimer() < 40000);
 		
 		li $v0, RESET_CORE_TIMER
 		syscall # resetCoreTimer();
 		
 		lui $t1,0xBF88
 		lw $t2,0x6050($t1)		# read the binary value from the 4 switches

		andi $t2,$t2,0x000F
 		
 		
 		
 		move $a0,$t2 			#
 		li $a1,0x00040002 		#
 		li $v0, PRINT_INT 		#
 		syscall 				# printInt(t2, 2);
 		
 		j while					# }
 		jr $ra 					#

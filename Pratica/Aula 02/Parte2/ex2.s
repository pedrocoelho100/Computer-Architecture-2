		.equ READ_CORE_TIMER,11
 		.equ RESET_CORE_TIMER,12
 		.data
 		.text
 		.globl main
main: 	li $t0,0
	 	
for:	beqz $a0, endf

		li $v0, RESET_CORE_TIMER
 		syscall # resetCoreTimer();
 		
while:	li $v0,READ_CORE_TIMER 	
 		syscall 				
				
 		blt $v0,20000,while 	# while(readCoreTimer() < 20000);
 		
	 	j for					# }
endf:
 		jr $ra 					#

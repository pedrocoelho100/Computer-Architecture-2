		.equ READ_CORE_TIMER,11
 		.equ RESET_CORE_TIMER,12
 		.equ SFR_BASE_HI, 0xBF88 	# 16 MSbits of SFR area
 		.equ TRISE, 0x6100 			# TRISE address is 0xBF886100
 		.equ PORTE, 0x6110 			# PORTE address is 0xBF886110
 		.equ LATE, 0x6120 			# LATE address is 0xBF886120
 		.equ TRISB, 0x6040
 		.equ PORTB, 0x6050
 		.equ LATB, 0x6060
 									# TRIS a 0->saída; a 1->entrada
 									#PORT  porto de entrada;
									#LAT   saídas. 
		.text			
		.globl main

main:	subu $sp, $sp, 4
		sw $ra, 0($sp)
		
		li	$t3, 0
		
		# configurar porto RE0 como saída
		
		lui $t1, SFR_BASE_HI
		lw	$t2, TRISE($t1)
		andi $t2, $t2, 0xFFF0
		sw	$t2, TRISE($t1)
		
while:		
		lw 	$t2, LATE($t1)
		
		xori $t3, $t2, 0x0001
		andi $t3, $t3, 0x0001
		
		srl $t2, $t2, 1
		
		sll $t3, $t3, 3
		
		or	$t2, $t2, $t3
		sw 	$t2, LATE($t1)
		
	
		li	$a0, 750
		jal delay
	
		j	while
		
		
		lw $ra, 0($sp)
		addu $sp, $sp, 4
		
		jr	$ra


delay:	
ford:	beqz $a0, endfd

		li 	$v0, RESET_CORE_TIMER
 		syscall 					# resetCoreTimer();
 		
whiled:	li 	$v0, READ_CORE_TIMER 	
 		syscall 				
				
 		blt $v0, 20000, whiled 		# while(readCoreTimer() < 20000);
 		
 		sub $a0, $a0, 1
	 	j 	ford					# }
endfd:
 		jr 	$ra 					#

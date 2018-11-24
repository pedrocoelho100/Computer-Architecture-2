	.equ SFR_BASE_HI, 0xBF88 # 16 MSbits of SFR area
 	.equ TRISE, 0x6100 # TRISE address is 0xBF886100
	.equ PORTE, 0x6110 # PORTE address is 0xBF886110
 	.equ LATE, 0x6120 # LATE address is 0xBF886120
 	.data
	.text
	.globl main
	
	#RE0 a RE3
main:
	
	subu $sp,$sp,4
	sw	$ra,0($sp)
	
	li	$t0,0
	
	lui $t1, SFR_BASE_HI #
 	lw $t2, TRISE($t1) # READ (Mem_addr = 0xBF880000 + 0x6100)
 	andi $t2, $t2, 0xFFF0 # MODIFY (bit0=bit3=0 (0 means OUTPUT))
 	sw $t2, TRISE($t1)
	
	
while:
	lw	$t2, LATE($t1)
	andi $t2, $t2, 0xFFF0
	or 	$t2,$t2,$t0
	sw	$t2, LATE($t1)
	
	li	$a0,500
	jal	delay
	
	addiu $t0,$t0,1	
		
	j	while
	
	addu $sp,$sp,4
	lw	$ra,0($sp)
	
	jr	$ra	

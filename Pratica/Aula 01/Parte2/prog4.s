# Programa 4 – teste dos system calls de leitura e impressão de inteiros
#
#void main(void)
#{
# int value;
# while (1)
# {
# printStr("\nIntroduza um numero (sinal e módulo): ");
# value = readInt10();
# printStr("\nValor lido em base 2: ");
# printInt(value, 2);
# printStr("\nValor lido em base 16: ");
# printInt(value, 16);
# printStr("\nValor lido em base 10 (unsigned): ");
# printInt(value, 10);
# printStr("\nValor lido em base 10 (signed): ");
# printInt10(value);
# }
#} 
	
	.equ	printStr, 8
	.equ	printInt, 6
	.equ	printInt10, 7
	.data
msg: 	.asciiz "\nIntroduza um numero (sinal e módulo): "
msg2: 	.asciiz "\nValor lido em base 2: "
msg3: 	.asciiz "\nValor lido em base 16: "
msg4: 	.asciiz "\nValor lido em base 10 (unsigned): "
msg5: 	.asciiz "\nValor lido em base 10 (signed): "
	
	.text
 	.globl 	main

main:	
while:	
	la $v0, printStr
	la $a0, msg
	syscall
	
	la $v0, 5
	syscall 		#readInt10()
	move $t0, $v0		#value = readInt10(); 
	
	la $v0, printStr
	la $a0, msg2
	syscall
	
	la $v0, printInt
	move $a0, $t0
	li $a1, 2
	syscall			#printInt(value, 2);
	
	la $v0, printStr
	la $a0, msg3
	syscall
	
	la $v0, printInt
	move $a0, $t0
	li $a1, 16
	syscall			#printInt(value, 16);
	
	la $v0, printStr
	la $a0, msg4
	syscall
	
	la $v0, printInt
	move $a0, $t0
	li $a1, 10
	syscall			#printInt(value, 10);
	
	la $v0, printStr
	la $a0, msg5
	syscall
	
	la $v0, printInt10
	move $a0, $t0
	syscall			#printInt10(value);
	
	j while

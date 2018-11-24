#define STR_MAX_SIZE 20
#char *strcat(char *, char *);
#char *strcpy(char *, char *);
#int strlen(char *);
#int main(void)
#{
# static char str1[STR_MAX_SIZE + 1];
# static char str2[STR_MAX_SIZE + 1];
# static char str3[2 * STR_MAX_SIZE + 1];
# printStr("Introduza 2 strings: ");
# readStr( str1, STR_MAX_SIZE );
# readStr( str2, STR_MAX_SIZE );
# printStr("Resultados:\n");
# prinInt( strlen(str1), 10 );
# prinInt( strlen(str2), 10 );
# strcpy(str3, str1);
# printStr( strcat(str3, str2) );
# printInt10( strcmp(str1, str2) );
# return 0;
#} 

	.equ 	STR_MAX_SIZE, 20
	.equ	printStr, 8
	.equ	printInt, 6
	.equ	printInt10, 7
	.equ	readStr, 9
	.data
msg: 	.asciiz "Introduza 2 strings: "
msg2:	.asciiz "Resultados:\n"
str1:	.space 21
str2:	.space 21
str3:	.space 41
	.text
 	.globl 	main
 	
main:	subu $sp,$sp,4
	sw $ra,0($sp)
		
	la $v0, printStr
	la $a0, msg
	syscall
	
	la $v0, readStr
	la $a0, str1
	la $a1, STR_MAX_SIZE
	syscall
	
	la $v0, readStr
	la $a0, str2
	la $a1, STR_MAX_SIZE
	syscall
	
	la $v0, printStr
	la $a0, msg2
	syscall
	
	la $a0, str1
	jal strlen
	
	move $a0, $v0
	li $a1, 10
	la $v0, printInt
	syscall
	
	la $a0, str2
	jal strlen
	
	move $a0, $v0
	li $a1, 10
	la $v0, printInt
	syscall
	
	la $a0, str3
	la $a1, str1
	jal strcpy
	
	la $a0, str3
	la $a1, str2
	jal strcat
	
	move $a0,$v0
	la $v0, printStr
	syscall
	
	la $a0, str1
	la $a1, str2
	jal strcmp
	
	move $a0, $v0
	la $v0, printInt10
	syscall
	
	li $v0,0
	
	lw $ra,0($sp)
	addu $sp,$sp,4
	
	jr $ra

strlen: li $t0,0
for:	lb $t1,0($a0)
	beqz $t1,endf
	addi $t0,$t0,1
	addiu $a0,$a0,1
	j for
endf:	move $v0, $t0
	jr $ra
	
strcat: subu $sp,$sp,4
	sw $ra,0($sp)
	
	move $t0,$a0
	
	lb $t1,0($a0)
for1:	beqz $t1,endf1
	addiu $a0, $a0, 1
	
	jal strcpy	
	
	j for1
endf1:
	move $v0, $t0
	lw $ra, 0($sp)
	addiu $sp,$sp,4
	
	jr $ra
	
strcpy:	move $t0, $a0
for2:	
	lb $t1, 0($a1)
	sb $t1, 0($a0)
	beqz $t1,endf2
	addiu $a0, $a0, 1
	addiu $a1, $a1, 1
	j for2
endf2:
	move $v0, $t0
	jr $ra
	
strcmp:	
for3:	lb $t0, 0($a0)
	lb $t1, 0($a1)
	bne $t0,$t1,endf3
	beqz $t0,endf
	addiu $a0,$a0,1
	addiu $a1,$a1,1
	j for3
endf3:
	subu $t2,$t0,$t1
	move $v0, $t2
	jr $ra	



	

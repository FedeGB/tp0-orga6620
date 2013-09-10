	.file	1 "tp0.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"-V\000"
	.align	2
$LC1:
	.ascii	"Version: %d\n\000"
	.align	2
$LC2:
	.ascii	"-h\000"
	.align	2
$LC3:
	.ascii	"Comandos y argumentos disponibles:\n\000"
	.align	2
$LC4:
	.ascii	"-V Version del programa\n\000"
	.align	2
$LC5:
	.ascii	"[File...] (Archivo/s de entrada)\n\000"
	.align	2
$LC6:
	.ascii	"En caso de no pasar archivos se toma la entrada estandar"
	.ascii	"\n\000"
	.align	2
$LC7:
	.ascii	"Cada linea se cuenta hasta un enter\n\000"
	.align	2
$LC8:
	.ascii	"Para finalizar el programa estando con la entrada estand"
	.ascii	"ar\000"
	.align	2
$LC9:
	.ascii	" pulsar 'ctrl+d' para un correcto cierre del mismo\000"
	.align	2
$LC10:
	.ascii	"r\000"
	.align	2
$LC11:
	.ascii	"No se pudo abrir el archivo: %s\n\000"
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,56,$31		# vars= 16, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,56
	.cprestore 16
	sw	$31,48($sp)
	sw	$fp,44($sp)
	sw	$28,40($sp)
	move	$fp,$sp
	sw	$4,56($fp)
	sw	$5,60($fp)
	sw	$0,24($fp)
	lw	$3,56($fp)
	li	$2,2			# 0x2
	bne	$3,$2,$L18
	lw	$2,60($fp)
	addu	$2,$2,4
	lw	$4,0($2)
	la	$5,$LC0
	la	$25,strcmp
	jal	$31,$25
	bne	$2,$0,$L19
	la	$4,$LC1
	li	$5,3			# 0x3
	la	$25,printf
	jal	$31,$25
	sw	$0,36($fp)
	b	$L17
$L19:
	lw	$2,60($fp)
	addu	$2,$2,4
	lw	$4,0($2)
	la	$5,$LC2
	la	$25,strcmp
	jal	$31,$25
	bne	$2,$0,$L18
	la	$4,$LC3
	la	$25,printf
	jal	$31,$25
	la	$4,$LC4
	la	$25,printf
	jal	$31,$25
	la	$4,$LC5
	la	$25,printf
	jal	$31,$25
	la	$4,$LC6
	la	$25,printf
	jal	$31,$25
	la	$4,$LC7
	la	$25,printf
	jal	$31,$25
	la	$4,$LC8
	la	$25,printf
	jal	$31,$25
	la	$4,$LC9
	la	$25,printf
	jal	$31,$25
	sw	$0,36($fp)
	b	$L17
$L18:
	lw	$3,56($fp)
	li	$2,1			# 0x1
	bne	$3,$2,$L21
	la	$4,__sF
	la	$25,procesarArchivo
	jal	$31,$25
	sw	$2,24($fp)
	b	$L22
$L21:
	li	$2,1			# 0x1
	sw	$2,28($fp)
$L23:
	lw	$2,28($fp)
	lw	$3,56($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L25
	b	$L22
$L25:
	lw	$2,28($fp)
	sll	$3,$2,2
	lw	$2,60($fp)
	addu	$2,$3,$2
	lw	$4,0($2)
	la	$5,$LC10
	la	$25,fopen
	jal	$31,$25
	sw	$2,32($fp)
	lw	$2,32($fp)
	bne	$2,$0,$L26
	lw	$2,28($fp)
	sll	$3,$2,2
	lw	$2,60($fp)
	addu	$2,$3,$2
	la	$4,__sF+176
	la	$5,$LC11
	lw	$6,0($2)
	la	$25,fprintf
	jal	$31,$25
	li	$2,1			# 0x1
	sw	$2,36($fp)
	b	$L17
$L26:
	lw	$4,32($fp)
	la	$25,procesarArchivo
	jal	$31,$25
	sw	$2,24($fp)
	lw	$2,24($fp)
	beq	$2,$0,$L27
	lw	$2,24($fp)
	sw	$2,36($fp)
	b	$L17
$L27:
	lw	$4,32($fp)
	la	$25,fclose
	jal	$31,$25
	sw	$0,32($fp)
	lw	$2,28($fp)
	addu	$2,$2,1
	sw	$2,28($fp)
	b	$L23
$L22:
	lw	$2,24($fp)
	sw	$2,36($fp)
$L17:
	lw	$2,36($fp)
	move	$sp,$fp
	lw	$31,48($sp)
	lw	$fp,44($sp)
	addu	$sp,$sp,56
	j	$31
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"

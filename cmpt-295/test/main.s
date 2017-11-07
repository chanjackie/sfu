	.file	"main.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"The sum of %ld, %ld, %ld, %ld, %ld, %ld is %ld.\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.section	.text.startup,"ax",@progbits
.LHOTB1:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	x(%rip), %esi
	movl	$y, %edi
	call	sum
	subq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	y+24(%rip), %r9
	movq	y+16(%rip), %r8
	movq	y+8(%rip), %rcx
	movq	y(%rip), %rdx
	movl	$.LC0, %esi
	pushq	%rax
	.cfi_def_cfa_offset 32
	pushq	y+40(%rip)
	.cfi_def_cfa_offset 40
	movl	$1, %edi
	pushq	y+32(%rip)
	.cfi_def_cfa_offset 48
	xorl	%eax, %eax
	call	__printf_chk
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE1:
	.section	.text.startup
.LHOTE1:
	.globl	y
	.data
	.align 32
	.type	y, @object
	.size	y, 48
y:
	.quad	27
	.quad	72
	.quad	15
	.quad	101
	.quad	22
	.quad	58
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	6
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

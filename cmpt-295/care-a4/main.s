	.file	"main.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%2x"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	print_matrix
	.type	print_matrix, @function
print_matrix:
.LFB24:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movl	$4, %r14d
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movslq	%esi, %r13
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %r12
.L2:
	leaq	4(%r12), %rbp
	movq	%r12, %rbx
.L3:
	movzbl	(%rbx), %edx
	xorl	%eax, %eax
	movl	$.LC0, %esi
	movl	$1, %edi
	addq	$1, %rbx
	call	__printf_chk
	cmpq	%rbp, %rbx
	jne	.L3
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	addq	%r13, %r12
	call	_IO_putc
	subl	$1, %r14d
	jne	.L2
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	jmp	_IO_putc
	.cfi_endproc
.LFE24:
	.size	print_matrix, .-print_matrix
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.section	.text.startup,"ax",@progbits
.LHOTB2:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$4, %ecx
	movl	$C, %edx
	movl	$B, %esi
	movl	$A, %edi
	call	matrix_prod
	movl	$4, %esi
	movl	$A, %edi
	call	print_matrix
	movl	$4, %esi
	movl	$B, %edi
	call	print_matrix
	movl	$4, %esi
	movl	$C, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	print_matrix
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE2:
	.section	.text.startup
.LHOTE2:
	.comm	C,16,16
	.globl	B
	.data
	.align 16
	.type	B, @object
	.size	B, 16
B:
	.byte	10
	.byte	12
	.byte	14
	.byte	5
	.byte	12
	.byte	10
	.byte	1
	.byte	1
	.byte	12
	.byte	0
	.byte	12
	.byte	10
	.byte	12
	.byte	0
	.byte	1
	.byte	10
	.globl	A
	.align 16
	.type	A, @object
	.size	A, 16
A:
	.byte	4
	.byte	11
	.byte	10
	.byte	3
	.byte	10
	.byte	6
	.byte	2
	.byte	1
	.byte	6
	.byte	3
	.byte	14
	.byte	13
	.byte	8
	.byte	5
	.byte	2
	.byte	0
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

	.file	"main.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%4d"
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
	movsbl	(%rbx), %edx
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
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	xorl	%ebp, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
.L9:
	movl	%ebp, %r12d
	xorl	%ebx, %ebx
.L10:
	movl	%ebx, %r8d
	movl	%r12d, %ecx
	movl	$4, %edx
	movl	$B, %esi
	movl	$A, %edi
	call	dot_prod
	movb	%al, C(%rbx,%rbp,4)
	addq	$1, %rbx
	cmpq	$4, %rbx
	jne	.L10
	addq	$1, %rbp
	cmpq	$4, %rbp
	jne	.L9
	movl	$4, %esi
	movl	$A, %edi
	call	print_matrix
	movl	$4, %esi
	movl	$B, %edi
	call	print_matrix
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	movl	$4, %esi
	movl	$C, %edi
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
	.byte	2
	.byte	-1
	.byte	2
	.byte	-2
	.byte	2
	.byte	-5
	.byte	-4
	.byte	2
	.byte	-1
	.byte	-1
	.byte	5
	.byte	0
	.byte	-1
	.byte	2
	.byte	-2
	.byte	-1
	.globl	A
	.align 16
	.type	A, @object
	.size	A, 16
A:
	.byte	3
	.byte	0
	.byte	1
	.byte	4
	.byte	-5
	.byte	1
	.byte	-1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	-2
	.byte	0
	.byte	7
	.byte	3
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

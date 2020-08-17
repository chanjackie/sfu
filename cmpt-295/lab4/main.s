	.file	"main.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Original values are: x=%d, y=%d.\n"
	.align 8
.LC1:
	.string	"Final values are: x=%d, y=%d.\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.section	.text.startup,"ax",@progbits
.LHOTB2:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	subq	$72, %rsp
	.cfi_def_cfa_offset 80
	movl	$9, %ecx
	movl	$6, %edx
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$6, 8(%rsp)
	movl	$9, 12(%rsp)
	call	__printf_chk
	leaq	12(%rsp), %rdx
	leaq	8(%rsp), %rsi
	leaq	16(%rsp), %rdi
	call	proc1
	movl	12(%rsp), %ecx
	movl	8(%rsp), %edx
	movl	$.LC1, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	leaq	16(%rsp), %rdi
	call	puts
	movq	56(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L5
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE2:
	.section	.text.startup
.LHOTE2:
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

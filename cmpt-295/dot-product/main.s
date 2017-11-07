	.file	"main.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"The dot product of (%ld,%ld) and (%ld,%ld) is %ld.\n"
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
	movl	$y, %esi
	movl	$x, %edi
	call	dot
	subq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	y+8(%rip), %r9
	movq	y(%rip), %r8
	movq	x+8(%rip), %rcx
	movq	x(%rip), %rdx
	movl	$.LC0, %esi
	pushq	%rax
	.cfi_def_cfa_offset 32
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	addq	$24, %rsp
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
	.align 16
	.type	y, @object
	.size	y, 16
y:
	.quad	18
	.quad	-4
	.globl	x
	.align 16
	.type	x, @object
	.size	x, 16
x:
	.quad	5
	.quad	12
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

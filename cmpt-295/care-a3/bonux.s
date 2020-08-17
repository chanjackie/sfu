	.file	"bonux.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	" of"
.LC1:
	.string	" %2X"
.LC2:
	.string	"Well done!"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB3:
	.section	.text.startup,"ax",@progbits
.LHOTB3:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	$12, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	xorl	%ebp, %ebp
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
.L2:
	xorl	%ebx, %ebx
.L5:
	movl	%ebx, %r8d
	movl	%ebp, %ecx
	movl	$4, %edx
	movl	$B, %esi
	movl	$A, %edi
	call	dot_prod
#APP
# 30 "bonux.c" 1
	movl %edx, %ecx
	
# 0 "" 2
#NO_APP
	testl	%ecx, %ecx
	je	.L3
	leal	-1(%r12), %r13d
	movl	%r12d, %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	movl	%r13d, %r12d
	call	__printf_chk
.L4:
	addl	$1, %ebx
	cmpl	$4, %ebx
	jne	.L5
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	addl	$1, %ebp
	call	_IO_putc
	cmpl	$4, %ebp
	jne	.L2
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc
	testl	%r12d, %r12d
	je	.L11
	popq	%rax
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	.cfi_restore_state
	movzbl	%al, %edx
	movl	$.LC1, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	jmp	.L4
.L11:
	popq	%rdx
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	movl	$.LC2, %edi
	jmp	puts
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE3:
	.section	.text.startup
.LHOTE3:
	.comm	C,16,16
	.globl	B
	.data
	.align 16
	.type	B, @object
	.size	B, 16
B:
	.byte	27
	.byte	54
	.byte	-89
	.byte	-18
	.byte	12
	.byte	36
	.byte	-100
	.byte	25
	.byte	-23
	.byte	28
	.byte	57
	.byte	46
	.byte	-6
	.byte	-14
	.byte	107
	.byte	7
	.globl	A
	.align 16
	.type	A, @object
	.size	A, 16
A:
	.byte	32
	.byte	-15
	.byte	38
	.byte	-26
	.byte	-52
	.byte	112
	.byte	-27
	.byte	38
	.byte	52
	.byte	-33
	.byte	64
	.byte	-22
	.byte	-22
	.byte	62
	.byte	-44
	.byte	13
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

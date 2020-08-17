	.file	"main.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Average of %ld cycles.\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.section	.text.startup,"ax",@progbits
.LHOTB1:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB38:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	xorl	%edi, %edi
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	xorl	%eax, %eax
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movl	$A, %ebx
	xorl	%r12d, %r12d
	movq	%rbx, %r13
	call	time
	movl	%eax, %edi
	call	srand
	call	newLL
	movq	%rax, %rbp
	.p2align 4,,10
	.p2align 3
.L2:
	leal	(%r12,%r12), %eax
	addl	$1, %r12d
	addq	$4, %r13
	movl	%eax, -4(%r13)
	call	rand
	movl	%eax, %r14d
	call	rand
	movslq	%r14d, %rcx
	movl	%r14d, %edx
	imulq	$-2147418109, %rcx, %rcx
	sarl	$31, %edx
	shrq	$32, %rcx
	addl	%r14d, %ecx
	sarl	$14, %ecx
	subl	%edx, %ecx
	movl	%ecx, %edx
	sall	$15, %edx
	subl	%ecx, %edx
	movslq	%eax, %rcx
	imulq	$-2147450879, %rcx, %rcx
	subl	%edx, %r14d
	cltd
	sall	$16, %r14d
	shrq	$32, %rcx
	addl	%eax, %ecx
	sarl	$15, %ecx
	subl	%edx, %ecx
	movl	%ecx, %edx
	sall	$16, %edx
	subl	%ecx, %edx
	subl	%edx, %eax
	orl	%r14d, %eax
	cltd
	idivl	%r12d
	movl	-4(%r13), %eax
	movslq	%edx, %rdx
	movl	A(,%rdx,4), %ecx
	movl	%ecx, -4(%r13)
	cmpl	$300, %r12d
	movl	%eax, A(,%rdx,4)
	jne	.L2
	movl	$A+1200, %r12d
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%rbx), %esi
	movq	%rbp, %rdi
	addq	$4, %rbx
	call	appendLL
	cmpq	%rbx, %r12
	jne	.L3
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L5:
#APP
# 44 "main.c" 1
	cpuid
	rdtscp
	movl %eax, %esi
	
# 0 "" 2
#NO_APP
	movq	%rbp, %rdi
	movl	%esi, start_time(%rip)
	movl	%r12d, %esi
	call	LLsearch
	movslq	%r12d, %rdi
	movl	%eax, Q(,%rdi,4)
#APP
# 56 "main.c" 1
	cpuid
	rdtscp
	movl %eax, %esi
	
# 0 "" 2
#NO_APP
	movl	%esi, end_time(%rip)
	subl	start_time(%rip), %esi
	xorl	%eax, %eax
	cmpl	$4000, %esi
	movl	%esi, cycles(,%rdi,4)
	setge	%al
	subl	%eax, %r12d
	addl	$1, %r12d
	cmpl	$599, %r12d
	jle	.L5
	movl	$cycles, %eax
	movl	$cycles+2400, %esi
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L6:
	movslq	(%rax), %rdx
	addq	$4, %rax
	addq	%rdx, %rcx
	cmpq	%rax, %rsi
	jne	.L6
	movq	%rcx, %rax
	movabsq	$7870610804782742023, %rdx
	movq	%rcx, total(%rip)
	imulq	%rdx
	sarq	$63, %rcx
	movl	$1, %edi
	movl	$.LC0, %esi
	xorl	%eax, %eax
	sarq	$8, %rdx
	subq	%rcx, %rdx
	call	__printf_chk
	popq	%rbx
	.cfi_def_cfa_offset 40
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	jmp	freeLL
	.cfi_endproc
.LFE38:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE1:
	.section	.text.startup
.LHOTE1:
	.globl	end_time
	.data
	.align 4
	.type	end_time, @object
	.size	end_time, 4
end_time:
	.long	125
	.globl	start_time
	.align 4
	.type	start_time, @object
	.size	start_time, 4
start_time:
	.long	150
	.comm	total,8,8
	.comm	cycles,2400,32
	.comm	Q,2400,32
	.comm	P,2400,32
	.comm	A,1200,32
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

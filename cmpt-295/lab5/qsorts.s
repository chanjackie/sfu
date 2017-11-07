	.file	"qsorts.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	qsort295_1
	.type	qsort295_1, @function
qsort295_1:
.LFB0:
	.cfi_startproc
	cmpl	$1, %esi
	jle	.L13
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	%esi, %r13d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %r12
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
.L10:
	movl	(%r12), %edi
	movslq	%r13d, %rbx
	movl	%r13d, %esi
	subq	$1, %rbx
	movl	$-1, %edx
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%r12,%rbx,4), %r9d
	leal	-1(%rsi), %ebp
	cmpl	%r9d, %edi
	jl	.L4
	movslq	%edx, %rax
	leaq	4(%r12,%rax,4), %rax
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%rax, %r8
	addq	$4, %rax
	movl	-4(%rax), %ecx
	addl	$1, %edx
	cmpl	%ecx, %edi
	jg	.L5
	cmpl	%edx, %ebp
	jle	.L6
	movl	%r9d, (%r8)
	movl	%ecx, (%r12,%rbx,4)
.L4:
	subq	$1, %rbx
	movl	%ebp, %esi
	jmp	.L3
.L6:
	subl	%ebp, %r13d
	movq	%r12, %rdi
	leaq	4(%r12,%rbx,4), %r12
	subl	$1, %r13d
	call	qsort295_1
	cmpl	$1, %r13d
	jg	.L10
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_restore 12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_restore 13
	.cfi_def_cfa_offset 8
.L13:
	rep ret
	.cfi_endproc
.LFE0:
	.size	qsort295_1, .-qsort295_1
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	swap
	.type	swap, @function
swap:
.LFB2:
	.cfi_startproc
	movl	(%rdi), %eax
	movl	(%rsi), %edx
	movl	%edx, (%rdi)
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE2:
	.size	swap, .-swap
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	partition_1
	.type	partition_1, @function
partition_1:
.LFB3:
	.cfi_startproc
	movslq	%esi, %rdx
	movl	(%rdi), %r9d
	movl	$-1, %ecx
	leaq	(%rdi,%rdx,4), %r11
	movq	%rdx, %rax
	.p2align 4,,10
	.p2align 3
.L17:
	movl	-4(%r11), %esi
	subl	$1, %eax
	cmpl	%esi, %r9d
	jl	.L18
	movslq	%ecx, %rdx
	leaq	4(%rdi,%rdx,4), %rdx
	.p2align 4,,10
	.p2align 3
.L19:
	movq	%rdx, %r10
	addq	$4, %rdx
	movl	-4(%rdx), %r8d
	addl	$1, %ecx
	cmpl	%r8d, %r9d
	jg	.L19
	cmpl	%ecx, %eax
	jle	.L20
	movl	%esi, (%r10)
	movl	%r8d, -4(%r11)
.L18:
	subq	$4, %r11
	jmp	.L17
.L20:
	rep ret
	.cfi_endproc
.LFE3:
	.size	partition_1, .-partition_1
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	partition_2
	.type	partition_2, @function
partition_2:
.LFB4:
	.cfi_startproc
	leal	-1(%rsi), %eax
	movslq	%eax, %rdx
	testl	%eax, %eax
	leaq	(%rdi,%rdx,4), %r11
	movl	(%r11), %r8d
	jle	.L26
	leal	-2(%rsi), %eax
	movq	%rdi, %rdx
	leaq	4(%rdi,%rax,4), %r9
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L25:
	movl	(%rdx), %ecx
	cmpl	%ecx, %r8d
	jl	.L24
	movslq	%eax, %rsi
	addl	$1, %eax
	leaq	(%rdi,%rsi,4), %rsi
	movl	(%rsi), %r10d
	movl	%ecx, (%rsi)
	movl	%r10d, (%rdx)
.L24:
	addq	$4, %rdx
	cmpq	%r9, %rdx
	jne	.L25
	movl	(%r11), %r8d
	movslq	%eax, %rdx
	salq	$2, %rdx
.L23:
	addq	%rdx, %rdi
	movl	(%rdi), %edx
	movl	%r8d, (%rdi)
	movl	%edx, (%r11)
	ret
.L26:
	xorl	%edx, %edx
	xorl	%eax, %eax
	jmp	.L23
	.cfi_endproc
.LFE4:
	.size	partition_2, .-partition_2
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	qsort295_2
	.type	qsort295_2, @function
qsort295_2:
.LFB1:
	.cfi_startproc
	cmpl	$1, %esi
	jle	.L35
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	%esi, %ebx
	.p2align 4,,10
	.p2align 3
.L32:
	movl	%ebx, %esi
	movq	%r12, %rdi
	call	partition_2
	movslq	%eax, %rbp
	movq	%r12, %rdi
	subl	%ebp, %ebx
	movl	%ebp, %esi
	leaq	4(%r12,%rbp,4), %r12
	subl	$1, %ebx
	call	qsort295_2
	cmpl	$1, %ebx
	jg	.L32
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_restore 12
	.cfi_def_cfa_offset 8
.L35:
	rep ret
	.cfi_endproc
.LFE1:
	.size	qsort295_2, .-qsort295_2
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

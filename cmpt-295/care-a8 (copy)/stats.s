	.file	"stats.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	min_max_avg
	.type	min_max_avg, @function
min_max_avg:
.LFB26:
	.cfi_startproc
	testl	%esi, %esi
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movl	$0x7f800000, (%rcx)
	movq	56(%rsp), %r10
	movq	64(%rsp), %r11
	movq	80(%rsp), %rbx
	movq	88(%rsp), %rbp
	jle	.L67
	leal	-1(%rsi), %eax
	movq	%rdi, %r14
	movq	%rdi, -8(%rsp)
	leaq	8(%rdi,%rax,8), %rax
	movq	%rax, %r12
	movq	%rax, -24(%rsp)
	leal	-1(%rdx), %eax
	movq	%r12, %r13
	leaq	4(,%rax,4), %r15
	movl	%eax, -12(%rsp)
	.p2align 4,,10
	.p2align 3
.L7:
	testl	%edx, %edx
	jle	.L9
	movq	(%r14), %rax
	leaq	(%rax,%r15), %r12
	.p2align 4,,10
	.p2align 3
.L6:
	movss	(%rax), %xmm0
	movss	(%rcx), %xmm1
	ucomiss	%xmm0, %xmm1
	jbe	.L4
	movss	%xmm0, (%rcx)
.L4:
	addq	$4, %rax
	cmpq	%rax, %r12
	jne	.L6
.L9:
	addq	$8, %r14
	cmpq	%r13, %r14
	jne	.L7
	movq	-8(%rsp), %r13
	movq	-24(%rsp), %r12
	movl	$0xff800000, (%r8)
	.p2align 4,,10
	.p2align 3
.L44:
	testl	%edx, %edx
	jle	.L14
	movq	0(%r13), %rax
	leaq	(%rax,%r15), %rcx
	.p2align 4,,10
	.p2align 3
.L12:
	movss	(%rax), %xmm0
	ucomiss	(%r8), %xmm0
	jbe	.L10
	movss	%xmm0, (%r8)
.L10:
	addq	$4, %rax
	cmpq	%rax, %rcx
	jne	.L12
.L14:
	addq	$8, %r13
	cmpq	%r12, %r13
	jne	.L44
	movl	-12(%rsp), %eax
	movl	$0x00000000, (%r9)
	xorl	%r8d, %r8d
	leaq	4(,%rax,4), %r12
	.p2align 4,,10
	.p2align 3
.L45:
	testl	%edx, %edx
	jle	.L17
	movq	(%rdi,%r8,8), %rax
	movss	(%r9), %xmm0
	leaq	(%rax,%r12), %rcx
	.p2align 4,,10
	.p2align 3
.L15:
	addss	(%rax), %xmm0
	addq	$4, %rax
	cmpq	%rcx, %rax
	movss	%xmm0, (%r9)
	jne	.L15
.L17:
	addq	$1, %r8
	cmpl	%r8d, %esi
	jg	.L45
.L16:
	movl	%esi, %eax
	imull	%edx, %eax
	testl	%eax, %eax
	jle	.L18
	pxor	%xmm0, %xmm0
	movss	(%r9), %xmm1
	cvtsi2ss	%eax, %xmm0
	divss	%xmm0, %xmm1
	movss	%xmm1, (%r9)
.L19:
	testl	%esi, %esi
	jle	.L33
	leal	-1(%rdx), %eax
	movq	96(%rsp), %r8
	xorl	%ecx, %ecx
	leaq	4(,%rax,4), %r12
	.p2align 4,,10
	.p2align 3
.L32:
	cmpl	$0, %edx
	movl	$0x7f800000, (%rbx,%rcx,4)
	movl	$0xff800000, 0(%rbp,%rcx,4)
	movl	$0x00000000, (%r8)
	jle	.L68
	movq	(%rdi,%rcx,8), %rax
	leaq	(%rax,%r12), %r9
	.p2align 4,,10
	.p2align 3
.L30:
	movss	(%rax), %xmm0
	movss	(%rbx,%rcx,4), %xmm1
	ucomiss	%xmm0, %xmm1
	jbe	.L26
	movss	%xmm0, (%rbx,%rcx,4)
	movss	(%rax), %xmm0
.L26:
	ucomiss	0(%rbp,%rcx,4), %xmm0
	jbe	.L28
	movss	%xmm0, 0(%rbp,%rcx,4)
	movss	(%rax), %xmm0
.L28:
	addss	(%r8), %xmm0
	addq	$4, %rax
	cmpq	%rax, %r9
	movss	%xmm0, (%r8)
	jne	.L30
.L25:
	pxor	%xmm1, %xmm1
	cvtsi2ss	%edx, %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, (%r8)
.L31:
	addq	$1, %rcx
	addq	$4, %r8
	cmpl	%ecx, %esi
	jg	.L32
.L33:
	testl	%edx, %edx
	jle	.L1
	leal	-1(%rdx), %eax
	movq	72(%rsp), %r8
	leaq	4(,%rax,4), %rbx
	leal	-1(%rsi), %eax
	leaq	8(%rdi,%rax,8), %r9
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L43:
	cmpl	$0, %esi
	movl	$0x7f800000, (%r10,%rax)
	movq	%rdi, %rdx
	movl	$0xff800000, (%r11,%rax)
	movl	$0x00000000, (%r8)
	jle	.L69
	.p2align 4,,10
	.p2align 3
.L52:
	movq	%rax, %rcx
	addq	(%rdx), %rcx
	movss	(%r10,%rax), %xmm1
	movss	(%rcx), %xmm0
	ucomiss	%xmm0, %xmm1
	jbe	.L37
	movss	%xmm0, (%r10,%rax)
	movss	(%rcx), %xmm0
.L37:
	ucomiss	(%r11,%rax), %xmm0
	jbe	.L39
	movss	%xmm0, (%r11,%rax)
	movss	(%rcx), %xmm0
.L39:
	addss	(%r8), %xmm0
	addq	$8, %rdx
	cmpq	%rdx, %r9
	movss	%xmm0, (%r8)
	jne	.L52
.L36:
	pxor	%xmm1, %xmm1
	cvtsi2ss	%esi, %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, (%r8)
.L42:
	addq	$4, %rax
	addq	$4, %r8
	cmpq	%rax, %rbx
	jne	.L43
.L1:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L69:
	.cfi_restore_state
	jne	.L70
	movl	$0x7fc00000, (%r8)
	jmp	.L42
.L68:
	jne	.L71
	movl	$0x7fc00000, (%r8)
	jmp	.L31
.L18:
	movl	$0x7fc00000, (%r9)
	jmp	.L19
.L67:
	movl	$0xff800000, (%r8)
	movl	$0x00000000, (%r9)
	jmp	.L16
.L70:
	pxor	%xmm0, %xmm0
	jmp	.L36
.L71:
	pxor	%xmm0, %xmm0
	jmp	.L25
	.cfi_endproc
.LFE26:
	.size	min_max_avg, .-min_max_avg
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

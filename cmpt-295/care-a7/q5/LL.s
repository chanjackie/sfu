	.file	"LL.c"
	.text
	.p2align 4,,15
.globl LLsearch
	.type	LLsearch, @function
LLsearch:
.LFB21:
	.cfi_startproc
	movq	8(%rdi), %rdx
	testq	%rdx, %rdx
	je	.L2
	xorl	%eax, %eax
	cmpl	%esi, (%rdx)
	jne	.L4
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L10:
	addl	$1, %eax
	cmpl	%esi, (%rdx)
	je	.L9
.L4:
	movq	8(%rdx), %rdx
	testq	%rdx, %rdx
	jne	.L10
.L2:
	movl	$-1, %eax
.L5:
	rep
	ret
	.p2align 4,,10
	.p2align 3
.L9:
	rep
	ret
	.cfi_endproc
.LFE21:
	.size	LLsearch, .-LLsearch
	.p2align 4,,15
.globl lsearch
	.type	lsearch, @function
lsearch:
.LFB23:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L12
	xorl	%eax, %eax
	cmpl	%edx, (%rdi)
	jne	.L18
	jmp	.L20
	.p2align 4,,10
	.p2align 3
.L16:
	movl	4(%rdi), %ecx
	addq	$4, %rdi
	cmpl	%edx, %ecx
	je	.L14
.L18:
	addl	$1, %eax
	cmpl	%eax, %esi
	jg	.L16
.L12:
	movl	$-1, %eax
.L14:
	rep
	ret
.L20:
	rep
	ret
	.cfi_endproc
.LFE23:
	.size	lsearch, .-lsearch
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	" %d"
	.text
	.p2align 4,,15
.globl LLdump
	.type	LLdump, @function
LLdump:
.LFB22:
	.cfi_startproc
	testq	%rdi, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	je	.L28
	movq	8(%rdi), %rbx
	testq	%rbx, %rbx
	je	.L23
	.p2align 4,,10
	.p2align 3
.L26:
	movl	(%rbx), %esi
	xorl	%eax, %eax
	movl	$.LC0, %edi
	call	printf
	movq	8(%rbx), %rbx
	testq	%rbx, %rbx
	jne	.L26
.L23:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	jmp	_IO_putc
.L28:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 8
	movq	stdout(%rip), %rsi
	movb	$10, %dil
	jmp	_IO_putc
	.cfi_endproc
.LFE22:
	.size	LLdump, .-LLdump
	.p2align 4,,15
.globl appendLL
	.type	appendLL, @function
appendLL:
.LFB20:
	.cfi_startproc
	movq	%rbx, -16(%rsp)
	movq	%rbp, -8(%rsp)
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -16
	.cfi_offset 3, -24
	testq	%rdi, %rdi
	movq	%rdi, %rbx
	movl	%esi, %ebp
	je	.L34
	movl	$16, %edi
	call	malloc
	testq	%rax, %rax
	je	.L34
	movl	%ebp, (%rax)
	addl	$1, (%rbx)
	cmpq	$0, 8(%rbx)
	movq	$0, 8(%rax)
	je	.L35
	movq	16(%rbx), %rdx
.L32:
	movq	%rax, 8(%rdx)
.L33:
	movq	%rax, 16(%rbx)
.L34:
	movq	8(%rsp), %rbx
	movq	16(%rsp), %rbp
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L35:
	.cfi_restore_state
	movq	16(%rbx), %rdx
	testq	%rdx, %rdx
	jne	.L32
	movq	%rax, 8(%rbx)
	jmp	.L33
	.cfi_endproc
.LFE20:
	.size	appendLL, .-appendLL
	.p2align 4,,15
.globl newLL
	.type	newLL, @function
newLL:
.LFB18:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$24, %edi
	call	malloc
	testq	%rax, %rax
	je	.L37
	movl	$0, (%rax)
	movq	$0, 8(%rax)
	movq	$0, 16(%rax)
.L37:
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE18:
	.size	newLL, .-newLL
	.p2align 4,,15
.globl freeLL
	.type	freeLL, @function
freeLL:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	testq	%rdi, %rdi
	je	.L43
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L41
	.p2align 4,,10
	.p2align 3
.L44:
	movq	8(%rdi), %rbx
	call	free
	testq	%rbx, %rbx
	movq	%rbx, %rdi
	jne	.L44
.L41:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	free
	.p2align 4,,10
	.p2align 3
.L43:
	.cfi_restore_state
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE19:
	.size	freeLL, .-freeLL
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-18)"
	.section	.note.GNU-stack,"",@progbits

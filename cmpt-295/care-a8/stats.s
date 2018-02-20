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
	leal	-3(%rsi), %r11d
	movss	.LC0(%rip), %xmm0
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rcx, %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	testl	%r11d, %r11d
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
	movss	%xmm0, (%rcx)
	jle	.L2
	leal	-3(%rdx), %eax
	leal	-1(%rdx), %r14d
	movq	%rdi, %rbp
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L3:
	testl	%eax, %eax
	jle	.L22
	movq	0(%rbp), %r12
	xorl	%ecx, %ecx
	movq	%r12, %r10
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L261:
	movss	4(%r10), %xmm1
	ucomiss	%xmm1, %xmm0
	ja	.L144
	movss	8(%r10), %xmm1
	addl	$3, %ecx
	addq	$12, %r10
	minss	%xmm0, %xmm1
	cmpl	%eax, %ecx
	movaps	%xmm1, %xmm0
	jge	.L260
.L5:
	movss	(%r10), %xmm1
	ucomiss	%xmm1, %xmm0
	jbe	.L261
.L144:
	addl	$3, %ecx
	addq	$12, %r10
	cmpl	%eax, %ecx
	movaps	%xmm1, %xmm0
	jl	.L5
.L260:
	cmpl	%ecx, %edx
	jle	.L130
.L129:
	movslq	%ecx, %r10
	leaq	(%r12,%r10,4), %r10
	.p2align 4,,10
	.p2align 3
.L9:
	movss	(%r10), %xmm1
	addl	$1, %ecx
	addq	$4, %r10
	minss	%xmm0, %xmm1
	cmpl	%ecx, %edx
	movaps	%xmm1, %xmm0
	jg	.L9
	testl	%eax, %eax
	jle	.L10
.L130:
	movq	8(%rbp), %r12
	xorl	%ecx, %ecx
	movq	%r12, %r10
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L263:
	movss	4(%r10), %xmm1
	ucomiss	%xmm1, %xmm0
	ja	.L148
	movss	8(%r10), %xmm1
	addl	$3, %ecx
	addq	$12, %r10
	minss	%xmm0, %xmm1
	cmpl	%eax, %ecx
	movaps	%xmm1, %xmm0
	jge	.L262
.L12:
	movss	(%r10), %xmm1
	ucomiss	%xmm1, %xmm0
	jbe	.L263
.L148:
	addl	$3, %ecx
	addq	$12, %r10
	cmpl	%eax, %ecx
	movaps	%xmm1, %xmm0
	jl	.L12
.L262:
	cmpl	%ecx, %edx
	jle	.L133
.L132:
	movslq	%ecx, %r10
	leaq	(%r12,%r10,4), %r10
	.p2align 4,,10
	.p2align 3
.L15:
	movss	(%r10), %xmm1
	addl	$1, %ecx
	addq	$4, %r10
	minss	%xmm0, %xmm1
	cmpl	%ecx, %edx
	movaps	%xmm1, %xmm0
	jg	.L15
	testl	%eax, %eax
	jle	.L151
.L133:
	movq	16(%rbp), %rcx
	xorl	%r10d, %r10d
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L264:
	movss	4(%rcx), %xmm1
	ucomiss	%xmm1, %xmm0
	ja	.L153
	movss	8(%rcx), %xmm1
	addl	$3, %r10d
	addq	$12, %rcx
	minss	%xmm0, %xmm1
	cmpl	%eax, %r10d
	movaps	%xmm1, %xmm0
	jge	.L16
.L18:
	movss	(%rcx), %xmm1
	ucomiss	%xmm1, %xmm0
	jbe	.L264
.L153:
	addl	$3, %r10d
	addq	$12, %rcx
	cmpl	%eax, %r10d
	movaps	%xmm1, %xmm0
	jl	.L18
.L16:
	cmpl	%r10d, %edx
	jle	.L7
	movq	16(%rbp), %r12
	movslq	%r10d, %r13
	leaq	(%r12,%r13,4), %rcx
	movq	%rcx, -8(%rsp)
	movl	%r14d, %ecx
	subl	%r10d, %ecx
	leaq	1(%r13,%rcx), %r10
	movq	-8(%rsp), %rcx
	leaq	(%r12,%r10,4), %r10
	.p2align 4,,10
	.p2align 3
.L20:
	movss	(%rcx), %xmm1
	addq	$4, %rcx
	minss	%xmm0, %xmm1
	cmpq	%rcx, %r10
	movaps	%xmm1, %xmm0
	jne	.L20
.L7:
	addl	$3, %ebx
	addq	$24, %rbp
	cmpl	%r11d, %ebx
	jl	.L3
	cmpl	%ebx, %esi
	jle	.L265
.L134:
	movslq	%ebx, %rcx
	leal	-1(%rdx), %r14d
	leaq	(%rdi,%rcx,8), %rbp
	.p2align 4,,10
	.p2align 3
.L28:
	testl	%eax, %eax
	jle	.L160
	movq	0(%rbp), %rcx
	xorl	%r10d, %r10d
	jmp	.L24
	.p2align 4,,10
	.p2align 3
.L266:
	movss	4(%rcx), %xmm1
	ucomiss	%xmm1, %xmm0
	ja	.L157
	movss	8(%rcx), %xmm1
	addl	$3, %r10d
	addq	$12, %rcx
	minss	%xmm0, %xmm1
	cmpl	%eax, %r10d
	movaps	%xmm1, %xmm0
	jge	.L30
.L24:
	movss	(%rcx), %xmm1
	ucomiss	%xmm1, %xmm0
	jbe	.L266
.L157:
	addl	$3, %r10d
	addq	$12, %rcx
	cmpl	%eax, %r10d
	movaps	%xmm1, %xmm0
	jl	.L24
.L30:
	cmpl	%r10d, %edx
	jle	.L25
	movq	0(%rbp), %r12
	movslq	%r10d, %r13
	leaq	(%r12,%r13,4), %rcx
	movq	%rcx, -8(%rsp)
	movl	%r14d, %ecx
	subl	%r10d, %ecx
	leaq	1(%r13,%rcx), %r10
	movq	-8(%rsp), %rcx
	leaq	(%r12,%r10,4), %r10
	.p2align 4,,10
	.p2align 3
.L27:
	movss	(%rcx), %xmm1
	addq	$4, %rcx
	minss	%xmm0, %xmm1
	cmpq	%rcx, %r10
	movaps	%xmm1, %xmm0
	jne	.L27
.L25:
	addl	$1, %ebx
	addq	$8, %rbp
	cmpl	%ebx, %esi
	jg	.L28
	movss	%xmm0, (%r15)
	testl	%r11d, %r11d
	movss	.LC1(%rip), %xmm0
	movss	%xmm0, (%r8)
	jle	.L267
.L31:
	leal	-1(%rdx), %r12d
	movq	%rdi, %rbx
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L50:
	testl	%eax, %eax
	jle	.L51
	movq	(%rbx), %r13
	xorl	%ecx, %ecx
	movq	%r13, %r10
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L269:
	movss	4(%r10), %xmm1
	ucomiss	%xmm0, %xmm1
	ja	.L162
	movss	8(%r10), %xmm1
	addl	$3, %ecx
	addq	$12, %r10
	maxss	%xmm0, %xmm1
	cmpl	%eax, %ecx
	movaps	%xmm1, %xmm0
	jge	.L268
.L34:
	movss	(%r10), %xmm1
	ucomiss	%xmm0, %xmm1
	jbe	.L269
.L162:
	addl	$3, %ecx
	addq	$12, %r10
	cmpl	%eax, %ecx
	movaps	%xmm1, %xmm0
	jl	.L34
.L268:
	cmpl	%ecx, %edx
	jle	.L137
.L136:
	movslq	%ecx, %r10
	leaq	0(%r13,%r10,4), %r10
	.p2align 4,,10
	.p2align 3
.L38:
	movss	(%r10), %xmm1
	addl	$1, %ecx
	addq	$4, %r10
	maxss	%xmm0, %xmm1
	cmpl	%ecx, %edx
	movaps	%xmm1, %xmm0
	jg	.L38
	testl	%eax, %eax
	jle	.L39
.L137:
	movq	8(%rbx), %r13
	xorl	%ecx, %ecx
	movq	%r13, %r10
	jmp	.L41
	.p2align 4,,10
	.p2align 3
.L271:
	movss	4(%r10), %xmm1
	ucomiss	%xmm0, %xmm1
	ja	.L166
	movss	8(%r10), %xmm1
	addl	$3, %ecx
	addq	$12, %r10
	maxss	%xmm0, %xmm1
	cmpl	%eax, %ecx
	movaps	%xmm1, %xmm0
	jge	.L270
.L41:
	movss	(%r10), %xmm1
	ucomiss	%xmm0, %xmm1
	jbe	.L271
.L166:
	addl	$3, %ecx
	addq	$12, %r10
	cmpl	%eax, %ecx
	movaps	%xmm1, %xmm0
	jl	.L41
.L270:
	cmpl	%ecx, %edx
	jle	.L140
.L139:
	movslq	%ecx, %r10
	leaq	0(%r13,%r10,4), %r10
	.p2align 4,,10
	.p2align 3
.L44:
	movss	(%r10), %xmm1
	addl	$1, %ecx
	addq	$4, %r10
	maxss	%xmm0, %xmm1
	cmpl	%ecx, %edx
	movaps	%xmm1, %xmm0
	jg	.L44
	testl	%eax, %eax
	jle	.L169
.L140:
	movq	16(%rbx), %rcx
	xorl	%r10d, %r10d
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L272:
	movss	4(%rcx), %xmm1
	ucomiss	%xmm0, %xmm1
	ja	.L171
	movss	8(%rcx), %xmm1
	addl	$3, %r10d
	addq	$12, %rcx
	maxss	%xmm0, %xmm1
	cmpl	%eax, %r10d
	movaps	%xmm1, %xmm0
	jge	.L45
.L47:
	movss	(%rcx), %xmm1
	ucomiss	%xmm0, %xmm1
	jbe	.L272
.L171:
	addl	$3, %r10d
	addq	$12, %rcx
	cmpl	%eax, %r10d
	movaps	%xmm1, %xmm0
	jl	.L47
.L45:
	cmpl	%r10d, %edx
	jle	.L36
	movl	%r12d, %r15d
	movq	16(%rbx), %r13
	movslq	%r10d, %r14
	subl	%r10d, %r15d
	leaq	1(%r14,%r15), %r10
	leaq	0(%r13,%r14,4), %rcx
	leaq	0(%r13,%r10,4), %r10
	.p2align 4,,10
	.p2align 3
.L49:
	movss	(%rcx), %xmm1
	addq	$4, %rcx
	maxss	%xmm0, %xmm1
	cmpq	%rcx, %r10
	movaps	%xmm1, %xmm0
	jne	.L49
.L36:
	addl	$3, %ebp
	addq	$24, %rbx
	cmpl	%r11d, %ebp
	jl	.L50
.L32:
	cmpl	%ebp, %esi
	jle	.L52
	leal	-1(%rsi), %ecx
	movslq	%ebp, %r10
	leal	-1(%rdx), %r12d
	leaq	(%rdi,%r10,8), %rbx
	subl	%ebp, %ecx
	leaq	1(%r10,%rcx), %rcx
	leaq	(%rdi,%rcx,8), %rbp
	.p2align 4,,10
	.p2align 3
.L53:
	testl	%eax, %eax
	jle	.L178
	movq	(%rbx), %rcx
	xorl	%r10d, %r10d
	jmp	.L55
	.p2align 4,,10
	.p2align 3
.L273:
	movss	4(%rcx), %xmm1
	ucomiss	%xmm0, %xmm1
	ja	.L175
	movss	8(%rcx), %xmm1
	addl	$3, %r10d
	addq	$12, %rcx
	maxss	%xmm0, %xmm1
	cmpl	%eax, %r10d
	movaps	%xmm1, %xmm0
	jge	.L59
.L55:
	movss	(%rcx), %xmm1
	ucomiss	%xmm0, %xmm1
	jbe	.L273
.L175:
	addl	$3, %r10d
	addq	$12, %rcx
	cmpl	%eax, %r10d
	movaps	%xmm1, %xmm0
	jl	.L55
.L59:
	cmpl	%r10d, %edx
	jle	.L56
	movl	%r12d, %r15d
	movq	(%rbx), %r13
	movslq	%r10d, %r14
	subl	%r10d, %r15d
	leaq	1(%r14,%r15), %r10
	leaq	0(%r13,%r14,4), %rcx
	leaq	0(%r13,%r10,4), %r10
	.p2align 4,,10
	.p2align 3
.L58:
	movss	(%rcx), %xmm1
	addq	$4, %rcx
	maxss	%xmm0, %xmm1
	cmpq	%rcx, %r10
	movaps	%xmm1, %xmm0
	jne	.L58
.L56:
	addq	$8, %rbx
	cmpq	%rbx, %rbp
	jne	.L53
.L52:
	movss	%xmm0, (%r8)
	leal	-2(%rsi), %ebx
	pxor	%xmm0, %xmm0
	testl	%ebx, %ebx
	movss	%xmm0, (%r9)
	jle	.L179
	leal	-3(%rdx), %r8d
	leal	-1(%rdx), %ebp
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L61:
	testl	%r8d, %r8d
	jle	.L69
	movq	(%rdi,%r10,8), %r12
	xorl	%eax, %eax
	movq	%r12, %rcx
	.p2align 4,,10
	.p2align 3
.L62:
	movss	(%rcx), %xmm1
	addl	$3, %eax
	addq	$12, %rcx
	addss	-8(%rcx), %xmm1
	addss	-4(%rcx), %xmm1
	cmpl	%r8d, %eax
	addss	%xmm1, %xmm0
	jl	.L62
	cmpl	%eax, %edx
	jle	.L142
.L141:
	movslq	%eax, %rcx
	leaq	(%r12,%rcx,4), %rcx
	.p2align 4,,10
	.p2align 3
.L64:
	addl	$1, %eax
	addss	(%rcx), %xmm0
	addq	$4, %rcx
	cmpl	%eax, %edx
	jg	.L64
	testl	%r8d, %r8d
	jle	.L180
.L142:
	movq	8(%rdi,%r10,8), %rax
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L66:
	movss	(%rax), %xmm1
	addl	$3, %ecx
	addq	$12, %rax
	addss	-8(%rax), %xmm1
	addss	-4(%rax), %xmm1
	cmpl	%r8d, %ecx
	addss	%xmm1, %xmm0
	jl	.L66
.L65:
	cmpl	%ecx, %edx
	jle	.L67
	movl	%ebp, %r15d
	movq	8(%rdi,%r10,8), %r12
	movslq	%ecx, %r13
	subl	%ecx, %r15d
	leaq	1(%r13,%r15), %rcx
	leaq	(%r12,%r13,4), %rax
	leaq	(%r12,%rcx,4), %rcx
	.p2align 4,,10
	.p2align 3
.L68:
	addss	(%rax), %xmm0
	addq	$4, %rax
	cmpq	%rax, %rcx
	jne	.L68
.L67:
	addq	$2, %r10
	cmpl	%r10d, %ebx
	jg	.L61
	movl	%r11d, %eax
	shrl	%eax
	leal	2(%rax,%rax), %eax
.L60:
	cmpl	%eax, %esi
	jle	.L70
	leal	-1(%rsi), %ecx
	movslq	%eax, %rbx
	leal	-3(%rdx), %r8d
	leaq	(%rdi,%rbx,8), %r10
	leal	-1(%rdx), %r12d
	movl	%ecx, %r15d
	subl	%eax, %r15d
	leaq	1(%rbx,%r15), %rax
	leaq	(%rdi,%rax,8), %rbp
	.p2align 4,,10
	.p2align 3
.L71:
	testl	%r8d, %r8d
	jle	.L181
	movq	(%r10), %rax
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L72:
	movss	(%rax), %xmm1
	addl	$3, %ecx
	addq	$12, %rax
	addss	-8(%rax), %xmm1
	addss	-4(%rax), %xmm1
	cmpl	%r8d, %ecx
	addss	%xmm1, %xmm0
	jl	.L72
.L75:
	cmpl	%ecx, %edx
	jle	.L73
	movl	%r12d, %r15d
	movq	(%r10), %rbx
	movslq	%ecx, %r13
	subl	%ecx, %r15d
	leaq	1(%r13,%r15), %rcx
	leaq	(%rbx,%r13,4), %rax
	leaq	(%rbx,%rcx,4), %rcx
	.p2align 4,,10
	.p2align 3
.L74:
	addss	(%rax), %xmm0
	addq	$4, %rax
	cmpq	%rcx, %rax
	jne	.L74
.L73:
	addq	$8, %r10
	cmpq	%rbp, %r10
	jne	.L71
.L70:
	movl	%esi, %eax
	movss	.LC3(%rip), %xmm1
	imull	%edx, %eax
	testl	%eax, %eax
	jle	.L76
	pxor	%xmm1, %xmm1
	cvtsi2ss	%eax, %xmm1
	divss	%xmm1, %xmm0
	movaps	%xmm0, %xmm1
.L76:
	testl	%esi, %esi
	movss	%xmm1, (%r9)
	jle	.L104
	movq	80(%rsp), %r8
	leal	-1(%rsi), %eax
	leal	-3(%rdx), %ebx
	movq	88(%rsp), %r9
	movq	96(%rsp), %rcx
	leal	-1(%rdx), %r15d
	movq	%rdi, %rbp
	leaq	4(%r8,%rax,4), %r14
	.p2align 4,,10
	.p2align 3
.L103:
	testl	%ebx, %ebx
	movl	$0x7f800000, (%r8)
	movl	$0xff800000, (%r9)
	movl	$0x00000000, (%rcx)
	jle	.L183
	movq	0(%rbp), %rax
	xorl	%r12d, %r12d
	leaq	4(%rax), %r10
	addq	$8, %rax
	jmp	.L93
	.p2align 4,,10
	.p2align 3
.L274:
	movss	%xmm0, (%r8)
	movss	-8(%rax), %xmm0
.L83:
	movss	(%r9), %xmm3
	ucomiss	%xmm3, %xmm0
	jbe	.L241
.L275:
	movss	%xmm0, (%r9)
	movss	-8(%rax), %xmm0
	movss	(%r10), %xmm1
	movss	(%rax), %xmm2
.L89:
	addss	%xmm1, %xmm0
	addl	$3, %r12d
	addq	$12, %r10
	addq	$12, %rax
	cmpl	%ebx, %r12d
	addss	%xmm0, %xmm2
	addss	(%rcx), %xmm2
	movss	%xmm2, (%rcx)
	jge	.L80
.L93:
	movss	-8(%rax), %xmm0
	movss	(%r8), %xmm1
	ucomiss	%xmm0, %xmm1
	ja	.L274
	movss	(%r10), %xmm2
	ucomiss	%xmm2, %xmm1
	ja	.L251
	movss	(%rax), %xmm2
	ucomiss	%xmm2, %xmm1
	jbe	.L83
.L251:
	movss	%xmm2, (%r8)
	movss	-8(%rax), %xmm0
	movss	(%r9), %xmm3
	ucomiss	%xmm3, %xmm0
	ja	.L275
.L241:
	movss	(%r10), %xmm1
	ucomiss	%xmm3, %xmm1
	jbe	.L242
	movss	%xmm1, (%r9)
	movss	-8(%rax), %xmm0
	movss	(%r10), %xmm1
	movss	(%rax), %xmm2
	jmp	.L89
	.p2align 4,,10
	.p2align 3
.L242:
	movss	(%rax), %xmm2
	ucomiss	%xmm3, %xmm2
	jbe	.L89
	movss	%xmm2, (%r9)
	movss	-8(%rax), %xmm0
	movss	(%r10), %xmm1
	movss	(%rax), %xmm2
	jmp	.L89
.L183:
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L80:
	cmpl	%r12d, %edx
	jle	.L276
	movq	0(%rbp), %r10
	movslq	%r12d, %r13
	leaq	(%r10,%r13,4), %rax
	movq	%rax, -8(%rsp)
	movl	%r15d, %eax
	subl	%r12d, %eax
	leaq	1(%r13,%rax), %r12
	movq	-8(%rsp), %rax
	leaq	(%r10,%r12,4), %r10
	.p2align 4,,10
	.p2align 3
.L101:
	movss	(%rax), %xmm0
	movss	(%r8), %xmm1
	ucomiss	%xmm0, %xmm1
	jbe	.L97
	movss	%xmm0, (%r8)
	movss	(%rax), %xmm0
.L97:
	ucomiss	(%r9), %xmm0
	jbe	.L99
	movss	%xmm0, (%r9)
	movss	(%rax), %xmm0
.L99:
	addss	(%rcx), %xmm0
	addq	$4, %rax
	cmpq	%r10, %rax
	movss	%xmm0, (%rcx)
	jne	.L101
.L96:
	pxor	%xmm1, %xmm1
	cvtsi2ss	%edx, %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, (%rcx)
.L102:
	addq	$4, %r8
	addq	$4, %r9
	addq	$4, %rcx
	addq	$8, %rbp
	cmpq	%r8, %r14
	jne	.L103
.L104:
	testl	%edx, %edx
	jle	.L1
	movq	64(%rsp), %rbx
	leal	-1(%rdx), %eax
	movq	56(%rsp), %r10
	movq	72(%rsp), %rcx
	leal	-1(%rsi), %r12d
	leaq	4(%rbx,%rax,4), %rbp
	movq	%rbx, %r8
	movq	%rbx, %r13
	.p2align 4,,10
	.p2align 3
.L128:
	movq	%r8, %rdx
	movl	$0x7f800000, (%r10)
	movl	$0xff800000, (%r8)
	subq	%r13, %rdx
	testl	%r11d, %r11d
	movl	$0x00000000, (%rcx)
	jle	.L184
	leaq	16(%rdi), %rax
	xorl	%ebx, %ebx
	jmp	.L118
	.p2align 4,,10
	.p2align 3
.L277:
	movq	%rdx, %r14
	movq	%rdx, %r15
	addq	-8(%rax), %r14
	addq	(%rax), %r15
	movss	%xmm0, (%r10)
	movss	(%r9), %xmm0
.L108:
	movss	(%r8), %xmm3
	ucomiss	%xmm3, %xmm0
	jbe	.L245
.L278:
	movss	%xmm0, (%r8)
	movss	(%r9), %xmm0
	movss	(%r14), %xmm1
	movss	(%r15), %xmm2
.L114:
	addss	%xmm1, %xmm0
	addl	$3, %ebx
	addq	$24, %rax
	cmpl	%r11d, %ebx
	addss	%xmm0, %xmm2
	addss	(%rcx), %xmm2
	movss	%xmm2, (%rcx)
	jge	.L105
.L118:
	movq	%rdx, %r9
	addq	-16(%rax), %r9
	movss	(%r10), %xmm1
	movss	(%r9), %xmm0
	ucomiss	%xmm0, %xmm1
	ja	.L277
	movq	%rdx, %r14
	addq	-8(%rax), %r14
	movss	(%r14), %xmm2
	ucomiss	%xmm2, %xmm1
	jbe	.L244
	movss	%xmm2, (%r10)
	movq	%rdx, %r15
	addq	(%rax), %r15
	movss	(%r9), %xmm0
	movss	(%r8), %xmm3
	ucomiss	%xmm3, %xmm0
	ja	.L278
.L245:
	movss	(%r14), %xmm1
	ucomiss	%xmm3, %xmm1
	jbe	.L246
	movss	%xmm1, (%r8)
	movss	(%r9), %xmm0
	movss	(%r14), %xmm1
	movss	(%r15), %xmm2
	jmp	.L114
	.p2align 4,,10
	.p2align 3
.L244:
	movq	%rdx, %r15
	addq	(%rax), %r15
	movss	(%r15), %xmm2
	ucomiss	%xmm2, %xmm1
	jbe	.L108
	movss	%xmm2, (%r10)
	movss	(%r9), %xmm0
	jmp	.L108
	.p2align 4,,10
	.p2align 3
.L246:
	movss	(%r15), %xmm2
	ucomiss	%xmm3, %xmm2
	jbe	.L114
	movss	%xmm2, (%r8)
	movss	(%r9), %xmm0
	movss	(%r14), %xmm1
	movss	(%r15), %xmm2
	jmp	.L114
.L184:
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L105:
	cmpl	%ebx, %esi
	jle	.L279
	movl	%r12d, %r14d
	movslq	%ebx, %r9
	subl	%ebx, %r14d
	leaq	(%rdi,%r9,8), %rax
	leaq	1(%r9,%r14), %r9
	leaq	(%rdi,%r9,8), %rbx
	.p2align 4,,10
	.p2align 3
.L126:
	movq	%rdx, %r9
	addq	(%rax), %r9
	movss	(%r10), %xmm1
	movss	(%r9), %xmm0
	ucomiss	%xmm0, %xmm1
	jbe	.L122
	movss	%xmm0, (%r10)
	movss	(%r9), %xmm0
.L122:
	ucomiss	(%r8), %xmm0
	jbe	.L124
	movss	%xmm0, (%r8)
	movss	(%r9), %xmm0
.L124:
	addss	(%rcx), %xmm0
	addq	$8, %rax
	cmpq	%rax, %rbx
	movss	%xmm0, (%rcx)
	jne	.L126
.L121:
	pxor	%xmm1, %xmm1
	cvtsi2ss	%esi, %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, (%rcx)
.L127:
	addq	$4, %r8
	addq	$4, %r10
	addq	$4, %rcx
	cmpq	%rbp, %r8
	jne	.L128
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
.L279:
	.cfi_restore_state
	testl	%esi, %esi
	jne	.L280
	movl	$0x7fc00000, (%rcx)
	jmp	.L127
.L276:
	testl	%edx, %edx
	jne	.L281
	movl	$0x7fc00000, (%rcx)
	jmp	.L102
.L181:
	xorl	%ecx, %ecx
	jmp	.L75
.L69:
	testl	%edx, %edx
	jle	.L67
	movq	(%rdi,%r10,8), %r12
	xorl	%eax, %eax
	jmp	.L141
	.p2align 4,,10
	.p2align 3
.L169:
	xorl	%r10d, %r10d
	jmp	.L45
.L178:
	xorl	%r10d, %r10d
	jmp	.L59
.L51:
	testl	%edx, %edx
	jle	.L36
	movq	(%rbx), %r13
	xorl	%ecx, %ecx
	jmp	.L136
.L160:
	xorl	%r10d, %r10d
	jmp	.L30
.L151:
	xorl	%r10d, %r10d
	jmp	.L16
.L22:
	testl	%edx, %edx
	jle	.L7
	movq	0(%rbp), %r12
	xorl	%ecx, %ecx
	jmp	.L129
.L39:
	testl	%edx, %edx
	jle	.L36
	movq	8(%rbx), %r13
	xorl	%ecx, %ecx
	jmp	.L139
.L10:
	testl	%edx, %edx
	jle	.L7
	movq	8(%rbp), %r12
	xorl	%ecx, %ecx
	jmp	.L132
.L2:
	testl	%esi, %esi
	jg	.L282
	movss	.LC1(%rip), %xmm0
	jmp	.L52
.L179:
	xorl	%eax, %eax
	jmp	.L60
.L282:
	leal	-3(%rdx), %eax
	xorl	%ebx, %ebx
	jmp	.L134
.L280:
	movss	(%rcx), %xmm0
	jmp	.L121
.L281:
	movss	(%rcx), %xmm0
	jmp	.L96
.L265:
	movss	%xmm0, (%r15)
	movl	$0xff800000, (%r8)
	movss	.LC1(%rip), %xmm0
	jmp	.L31
.L180:
	xorl	%ecx, %ecx
	jmp	.L65
.L267:
	xorl	%ebp, %ebp
	jmp	.L32
	.cfi_endproc
.LFE26:
	.size	min_max_avg, .-min_max_avg
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	2139095040
	.align 4
.LC1:
	.long	4286578688
	.align 4
.LC3:
	.long	2143289344
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

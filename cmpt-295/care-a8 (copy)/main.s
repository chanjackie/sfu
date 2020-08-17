	.file	"main.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d%d"
.LC1:
	.string	"%f"
.LC2:
	.string	" min     >>>"
.LC3:
	.string	"    max   >>"
.LC4:
	.string	" %2d"
.LC5:
	.string	"  v    avg >"
.LC6:
	.string	"  v  v      "
.LC7:
	.string	"  v  v  v   "
.LC8:
	.string	" %2d %2d %2d   (Overall)"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC9:
	.string	"Sample %d completed in %d cycles.\n"
	.section	.rodata.str1.1
.LC10:
	.string	" %2d %2d %2d   "
.LC11:
	.string	"Average of %ld cycles.\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB12:
	.section	.text.startup,"ax",@progbits
.LHOTB12:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB60:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movl	$.LC0, %edi
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$16, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	leaq	4(%rsp), %rdx
	movq	%rsp, %rsi
	call	__isoc99_scanf
	movslq	(%rsp), %rdi
	salq	$3, %rdi
	call	malloc
	movl	(%rsp), %r9d
	movq	%rax, %rbp
	movslq	4(%rsp), %rdi
	testl	%r9d, %r9d
	jle	.L3
	movq	%rax, %rbx
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L6:
	salq	$2, %rdi
	call	malloc
	movslq	4(%rsp), %rdi
	movq	%rax, (%rbx)
	testl	%edi, %edi
	jle	.L4
	movq	%rax, %rsi
	xorl	%r14d, %r14d
	xorl	%r13d, %r13d
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L49:
	movq	(%rbx), %rsi
.L5:
	addq	%r14, %rsi
	movl	$.LC1, %edi
	xorl	%eax, %eax
	call	__isoc99_scanf
	movslq	4(%rsp), %rdi
	addl	$1, %r13d
	addq	$4, %r14
	cmpl	%r13d, %edi
	jg	.L49
.L4:
	addl	$1, %r12d
	addq	$8, %rbx
	cmpl	%r12d, (%rsp)
	jg	.L6
.L3:
	salq	$2, %rdi
	xorl	%r12d, %r12d
	call	malloc
	movslq	4(%rsp), %rdi
	movq	%rax, col_min(%rip)
	salq	$2, %rdi
	call	malloc
	movslq	4(%rsp), %rdi
	movq	%rax, col_max(%rip)
	salq	$2, %rdi
	call	malloc
	movslq	(%rsp), %rdi
	movq	%rax, col_avg(%rip)
	salq	$2, %rdi
	call	malloc
	movslq	(%rsp), %rdi
	movq	%rax, row_min(%rip)
	salq	$2, %rdi
	call	malloc
	movslq	(%rsp), %rdi
	movq	%rax, row_max(%rip)
	salq	$2, %rdi
	call	malloc
	movq	%rax, row_avg(%rip)
	.p2align 4,,10
	.p2align 3
.L8:
#APP
# 58 "main.c" 1
	cpuid
	rdtscp
	movl %eax, %esi
	
# 0 "" 2
#NO_APP
	pushq	row_avg(%rip)
	.cfi_def_cfa_offset 72
	movl	%esi, start_time(%rip)
	movl	$overall_avg, %r9d
	pushq	row_max(%rip)
	.cfi_def_cfa_offset 80
	pushq	row_min(%rip)
	.cfi_def_cfa_offset 88
	movl	$overall_max, %r8d
	pushq	col_avg(%rip)
	.cfi_def_cfa_offset 96
	pushq	col_max(%rip)
	.cfi_def_cfa_offset 104
	movl	$overall_min, %ecx
	pushq	col_min(%rip)
	.cfi_def_cfa_offset 112
	movl	52(%rsp), %edx
	movq	%rbp, %rdi
	movl	48(%rsp), %esi
	call	min_max_avg
#APP
# 69 "main.c" 1
	cpuid
	rdtscp
	movl %eax, %esi
	
# 0 "" 2
#NO_APP
	movl	%esi, end_time(%rip)
	subl	start_time(%rip), %esi
	movslq	%r12d, %rax
	addq	$48, %rsp
	.cfi_def_cfa_offset 64
	movl	%esi, cycles(,%rax,4)
	xorl	%eax, %eax
	cmpl	$20000, %esi
	setge	%al
	subl	%eax, %r12d
	addl	$1, %r12d
	cmpl	$19, %r12d
	jle	.L8
	xorl	%eax, %eax
	movl	$.LC2, %esi
	movl	$1, %edi
	call	__printf_chk
	movl	4(%rsp), %r8d
	xorl	%r12d, %r12d
	xorl	%ebx, %ebx
	testl	%r8d, %r8d
	jle	.L13
	.p2align 4,,10
	.p2align 3
.L35:
	movq	col_min(%rip), %rax
	movl	$.LC4, %esi
	movl	$1, %edi
	addl	$1, %ebx
	cvttss2si	(%rax,%r12), %edx
	xorl	%eax, %eax
	addq	$4, %r12
	call	__printf_chk
	cmpl	%ebx, 4(%rsp)
	jg	.L35
.L13:
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	xorl	%r12d, %r12d
	xorl	%ebx, %ebx
	call	_IO_putc
	movl	$1, %edi
	xorl	%eax, %eax
	movl	$.LC3, %esi
	call	__printf_chk
	movl	4(%rsp), %edi
	testl	%edi, %edi
	jle	.L11
	.p2align 4,,10
	.p2align 3
.L34:
	movq	col_max(%rip), %rax
	movl	$.LC4, %esi
	movl	$1, %edi
	addl	$1, %ebx
	cvttss2si	(%rax,%r12), %edx
	xorl	%eax, %eax
	addq	$4, %r12
	call	__printf_chk
	cmpl	%ebx, 4(%rsp)
	jg	.L34
.L11:
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	xorl	%r12d, %r12d
	xorl	%ebx, %ebx
	call	_IO_putc
	movl	$.LC5, %esi
	xorl	%eax, %eax
	movl	$1, %edi
	call	__printf_chk
	movl	4(%rsp), %esi
	testl	%esi, %esi
	jle	.L15
	.p2align 4,,10
	.p2align 3
.L33:
	movq	col_avg(%rip), %rax
	movl	$.LC4, %esi
	movl	$1, %edi
	addl	$1, %ebx
	cvttss2si	(%rax,%r12), %edx
	xorl	%eax, %eax
	addq	$4, %r12
	call	__printf_chk
	cmpl	%ebx, 4(%rsp)
	jg	.L33
.L15:
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	xorl	%r14d, %r14d
	xorl	%r13d, %r13d
	call	_IO_putc
	movl	$.LC6, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc
	movl	$.LC7, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc
	movl	(%rsp), %ecx
	testl	%ecx, %ecx
	jle	.L18
	.p2align 4,,10
	.p2align 3
.L31:
	movq	row_max(%rip), %rax
	movl	$.LC10, %esi
	movl	$1, %edi
	xorl	%r12d, %r12d
	xorl	%ebx, %ebx
	cvttss2si	(%rax,%r14), %ecx
	movq	row_min(%rip), %rax
	cvttss2si	(%rax,%r14), %edx
	movq	row_avg(%rip), %rax
	cvttss2si	(%rax,%r14), %r8d
	xorl	%eax, %eax
	call	__printf_chk
	movl	4(%rsp), %edx
	testl	%edx, %edx
	jle	.L24
	.p2align 4,,10
	.p2align 3
.L32:
	movq	0(%rbp,%r14,2), %rax
	movl	$.LC4, %esi
	movl	$1, %edi
	addl	$1, %ebx
	cvttss2si	(%rax,%r12), %edx
	xorl	%eax, %eax
	addq	$4, %r12
	call	__printf_chk
	cmpl	%ebx, 4(%rsp)
	jg	.L32
.L24:
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	addl	$1, %r13d
	addq	$4, %r14
	call	_IO_putc
	cmpl	%r13d, (%rsp)
	jg	.L31
.L18:
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	movl	$cycles+4, %r12d
	movl	$1, %ebx
	call	_IO_putc
	cvttss2si	overall_max(%rip), %ecx
	cvttss2si	overall_min(%rip), %edx
	movl	$.LC8, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	cvttss2si	overall_avg(%rip), %r8d
	call	__printf_chk
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc
	movl	cycles(%rip), %ecx
	movl	$1, %edx
	movl	$.LC9, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	movq	$0, total(%rip)
	call	__printf_chk
	.p2align 4,,10
	.p2align 3
.L20:
	movl	(%r12), %ecx
	addl	$1, %ebx
	xorl	%eax, %eax
	movl	%ebx, %edx
	movl	$.LC9, %esi
	movl	$1, %edi
	call	__printf_chk
	leal	-1(%rbx), %eax
	cmpl	$9, %eax
	jbe	.L25
	movslq	(%r12), %rax
	addq	%rax, total(%rip)
.L25:
	addq	$4, %r12
	cmpl	$20, %ebx
	jne	.L20
	movq	total(%rip), %rcx
	movabsq	$7378697629483820647, %rdx
	movl	$.LC11, %esi
	movl	$1, %edi
	xorl	%ebx, %ebx
	movq	%rbp, %r12
	movq	%rcx, %rax
	sarq	$63, %rcx
	imulq	%rdx
	xorl	%eax, %eax
	sarq	$2, %rdx
	subq	%rcx, %rdx
	call	__printf_chk
	movl	(%rsp), %eax
	testl	%eax, %eax
	jle	.L28
	.p2align 4,,10
	.p2align 3
.L30:
	movq	(%r12), %rdi
	addl	$1, %ebx
	addq	$8, %r12
	call	free
	cmpl	%ebx, (%rsp)
	jg	.L30
.L28:
	movq	%rbp, %rdi
	call	free
	movq	col_min(%rip), %rdi
	call	free
	movq	col_max(%rip), %rdi
	call	free
	movq	col_avg(%rip), %rdi
	call	free
	movq	row_min(%rip), %rdi
	call	free
	movq	row_max(%rip), %rdi
	call	free
	movq	row_avg(%rip), %rdi
	call	free
	movq	8(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L50
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
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
	ret
.L50:
	.cfi_restore_state
	call	__stack_chk_fail
	.cfi_endproc
.LFE60:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE12:
	.section	.text.startup
.LHOTE12:
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
	.comm	cycles,80,32
	.comm	row_avg,8,8
	.comm	row_max,8,8
	.comm	row_min,8,8
	.comm	col_avg,8,8
	.comm	col_max,8,8
	.comm	col_min,8,8
	.comm	overall_avg,4,4
	.comm	overall_max,4,4
	.comm	overall_min,4,4
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

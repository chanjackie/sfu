	.file	"main.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	get_byte_by_order
	.type	get_byte_by_order, @function
get_byte_by_order:
.LFB23:
	.cfi_startproc
	cmpl	$1, %esi
	je	.L7
	cmpl	$2, %esi
	je	.L8
	movzbl	%dil, %eax
	shrl	$24, %edi
	cmpl	$3, %esi
	cmove	%edi, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	movq	%rdi, %rax
	movzbl	%ah, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	andl	$16711680, %edi
	movl	%edi, %eax
	sarl	$16, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	get_byte_by_order, .-get_byte_by_order
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"x = %#.08x\n"
.LC2:
	.string	"x = %d\n"
.LC3:
	.string	"y = %#.08x\n"
.LC4:
	.string	"y = %u\n"
.LC5:
	.string	"x = "
.LC6:
	.string	"%02x"
.LC7:
	.string	"y = "
	.section	.text.unlikely
.LCOLDB8:
	.section	.text.startup,"ax",@progbits
.LHOTB8:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	$.LC1, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	xorl	%ebx, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movl	x(%rip), %edx
	movl	$1, %ebp
	call	__printf_chk
	movl	x(%rip), %edx
	movl	$.LC2, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	movl	y(%rip), %edx
	movl	$.LC3, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	movl	y(%rip), %edx
	movl	$.LC4, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	xorl	%eax, %eax
	movl	$.LC5, %esi
	movl	$1, %edi
	call	__printf_chk
	movl	x(%rip), %eax
	cmpl	$1, %ebx
	movzbl	%al, %edx
	je	.L29
.L11:
	cmpl	$2, %ebx
	je	.L30
	cmpl	$3, %ebx
	je	.L31
	xorl	%eax, %eax
	movl	$.LC6, %esi
	movl	$1, %edi
	call	__printf_chk
	cmpl	$4, %ebp
	je	.L15
.L16:
	movl	x(%rip), %eax
	addl	$1, %ebx
	addl	$1, %ebp
	cmpl	$1, %ebx
	movzbl	%al, %edx
	jne	.L11
.L29:
	movzbl	%ah, %edx
.L12:
	movl	$.LC6, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	jmp	.L16
.L31:
	shrl	$24, %eax
	movl	$.LC6, %esi
	movl	$1, %edi
	movl	%eax, %edx
	xorl	%eax, %eax
	call	__printf_chk
	.p2align 4,,10
	.p2align 3
.L15:
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	xorl	%ebx, %ebx
	call	_IO_putc
	movl	$.LC5, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
.L17:
	movl	%ebx, %esi
	movl	$x, %edi
	addl	$1, %ebx
	call	get_byte_by_addr
	movl	$.LC6, %esi
	movl	%eax, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	cmpl	$4, %ebx
	jne	.L17
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	xorl	%ebx, %ebx
	movl	$1, %ebp
	call	_IO_putc
	xorl	%eax, %eax
	movl	$.LC7, %esi
	movl	$1, %edi
	call	__printf_chk
	movl	y(%rip), %eax
	cmpl	$1, %ebx
	movzbl	%al, %edx
	je	.L32
.L19:
	cmpl	$2, %ebx
	je	.L33
	cmpl	$3, %ebx
	je	.L34
	xorl	%eax, %eax
	movl	$.LC6, %esi
	movl	$1, %edi
	call	__printf_chk
	cmpl	$4, %ebp
	je	.L23
.L24:
	movl	y(%rip), %eax
	addl	$1, %ebx
	addl	$1, %ebp
	cmpl	$1, %ebx
	movzbl	%al, %edx
	jne	.L19
.L32:
	movzbl	%ah, %edx
.L20:
	movl	$.LC6, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	jmp	.L24
.L34:
	shrl	$24, %eax
	movl	$.LC6, %esi
	movl	$1, %edi
	movl	%eax, %edx
	xorl	%eax, %eax
	call	__printf_chk
	.p2align 4,,10
	.p2align 3
.L23:
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	xorl	%ebx, %ebx
	call	_IO_putc
	movl	$.LC7, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
.L25:
	movl	%ebx, %esi
	movl	$y, %edi
	addl	$1, %ebx
	call	get_byte_by_addr
	movl	$.LC6, %esi
	movl	%eax, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	cmpl	$4, %ebx
	jne	.L25
	movq	stdout(%rip), %rsi
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	$10, %edi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_IO_putc
.L30:
	.cfi_restore_state
	andl	$16711680, %eax
	sarl	$16, %eax
	movl	%eax, %edx
	jmp	.L12
.L33:
	andl	$16711680, %eax
	sarl	$16, %eax
	movl	%eax, %edx
	jmp	.L20
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE8:
	.section	.text.startup
.LHOTE8:
	.globl	y
	.data
	.align 4
	.type	y, @object
	.size	y, 4
y:
	.long	2908479998
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	233876875
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

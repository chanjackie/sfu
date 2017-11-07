	.file	"times.c"
	.text
	.globl	times
	.type	times, @function
times:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	imull	%esi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	times, .-times
	.ident	"GCC: (Ubuntu 5.4.1-2ubuntu1~16.04) 5.4.1 20160904"
	.section	.note.GNU-stack,"",@progbits

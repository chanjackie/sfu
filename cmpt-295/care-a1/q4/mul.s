	.globl times
times:
	movl $0, %eax
loop:
	cmpl $0, %esi
	jle endl
	addl %edi, %eax
	decl %esi
	jmp loop
endl:
	ret

	.globl sqrt
sqrt:
	movl $0, %eax   
	movq $15, %rcx
loop:
	cmp $0, %rcx
	jle endl
	movq %rcx, %rdx
	movq $1, %rsi
bloop:
	cmp $1, %rdx
	jle endbl
	imul $2, %rsi
	dec %rdx
	jmp bloop
endbl:
	dec %rcx
	xor %esi, %eax
	mov %eax, %edx
	imul %edx, %edx
	cmp %edi, %edx
	jle loop
	xor %esi, %eax
	jmp loop	
endl:
	sub %edi, %edx
	cmp $5, %edx
	jl end
	inc %eax
end:
	ret

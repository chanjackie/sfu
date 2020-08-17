	.globl main
.string0:
	.string "The value of %ld! is %ld.\n"
main:
	movq	$0, %rbx  # for (n = 0; n <= 20; n++) 
loop:
	cmpq	$20, %rbx
	jg	endloop
	movq	%rbx, %rdi
	call	fact
	movq	$.string0, %rdi
	movq	%rbx, %rsi
	movq	%rax, %rdx
	xorl	%eax, %eax
	call	printf   # printf("The value of %ld! is %ld.\n", n, fact(n));
	incq	%rbx
	jmp	loop

endloop:
	ret


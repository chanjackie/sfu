	.globl sum_float

	# var map:
	#   %xmm0:  total
	#   %rdi:   F[n] (base pointer)
	#   %rsi:   n
	#   %rbp:   endptr

sum_float:
	push	%rbp
	movq %rsp, %r9				# r9 <- head(Q)
	subq $8, %r9
	movq $0, %r8				# i counter
	xorps	%xmm0, %xmm0            # total <- 0.0
	leaq	(%rdi, %rsi, 4), %rbp   # endptr <- F + n

loop:
	cmpq	%rsi, %r8             
	jge	endloop                 # while (F < endptr) {
	pushq %r15
	movq (%r9), %r15
	cmpq %r15, (%rdi)
	popq %r15
	jl xfsmall
	movq (%r9), %rdx
	subq $8, %r9
	jmp endx
xfsmall:
	movq (%rdi), %rdx
	addq $4, %rdi
endx:
	pushq %r15
	movq (%r9), %r15
	cmpq %r15, (%rdi)
	popq %r15
	jl yfsmall
	movq (%r9), %rcx
	subq $8, %r9
	jmp endy
yfsmall:
	movq (%rdi), %rcx
	addq $4, %rdi
endy:
	addq %rdx, %rcx
	push %rcx
	incq %r8
	jmp	loop                    # }

endloop:
	movq (%rsp), %xmm0
	addq $8, %rsp
	pop	%rbp
	ret


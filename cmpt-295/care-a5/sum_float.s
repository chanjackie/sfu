	.globl sum_float

	# var map:
	#   %xmm0:  total
	#   %rdi:   F[n] (base pointer)
	#   %rsi:   n
	#   %rbp:   endptr
	# 	%r14: 	head(Q)
	#	%r15:	i
	#	%r8:	x
	#	%r9:	y
sum_float:
	push	%rbp
	pushq %r14
	pushq %r15
	movq %rsp, %rcx
	movq $0, %r15				# i counter
	movq %rsp, %r14				# r14 <- head(Q)
	subq $8, %r14	
	xorps	%xmm0, %xmm0 
	xorps 	%xmm8, %xmm8
	xorps 	%xmm9, %xmm9
	xorps 	%xmm10, %xmm10
	xorps	%xmm11, %xmm11           # total <- 0.0
	leaq	(%rdi, %rsi, 4), %rbp   # endptr <- F + n
loop:
	cmpq	%rsi, %r15             
	jge	endloop                 # while (F < endptr) {
	cmpq %rsp, %r14
	jl fxLess
	cmpq %rdi, %rbp
	jle fxEmpty
	movss (%r14), %xmm10
	movss (%rdi), %xmm11
	cvttss2si %xmm10, %r8
	cvttss2si %xmm11, %r9
	cmpq %r8, %r9
	jle fxLess
fxEmpty:
	movss (%r14), %xmm8
	subq $8, %r14
	jmp xCheck
fxLess:
	movss (%rdi), %xmm8
	addq $4, %rdi
xCheck:
	cmpq %rsp, %r14
	jl fyLess
	cmpq %rdi, %rbp
	jle fyEmpty
	movss (%r14), %xmm10
	movss (%rdi), %xmm11
	cvttss2si %xmm10, %r8
	cvttss2si %xmm11, %r9
	cmpq %r8, %r9
	jle fyLess
fyEmpty:
	movss (%r14), %xmm9
	subq $8, %r14
	jmp yCheck
fyLess:
	movss (%rdi), %xmm9
	addq $4, %rdi
yCheck:
	addss %xmm8, %xmm9
	movq %xmm9, %r8
	pushq %r8
	incq %r15
	jmp	loop                    # }
endloop:
	cmpq %rsp, %rcx
	je endsum
	addss (%rsp), %xmm0
	addq $8, %rsp
	jmp endloop
endsum:
	popq %r15
	popq %r14
	pop	%rbp
	ret


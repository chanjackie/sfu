    .globl dot_prod
dot_prod:
	xorl %eax, %eax		
	movq $0, %r11		#counter k to 0
	movq $0, %r10
	movq $0, %r9
loop:
	cmp %rdx, %r11		#if k >= n, end
	jge endl
	pushq %rdi			#save matrix A
	pushq %rsi			#save matrix B
	pushq %rcx			#save i
	pushq %rdx			#save n
	imulq %rdx, %rcx	#i<-i*n
	addq %r11, %rcx		#i<-i + k
	addq %rcx, %rdi 	#A + i*n + k -> rdi
	imulq %r11, %rdx	
	addq %r8, %rdx		#k*n + j
	addq %rdx, %rsi 	#B + k*n + j -> rsi
	movq (%rsi), %rdx	#store value at address B + k*n + j -> rdx
	movq (%rdi), %rcx	#store value at address A + i*n + k -> rcx
	imulq %rdx, %rcx	#A_ik * B_kj
	addq %rcx, %r9
	addb %cl, %al	
	popq %rdx
	popq %rcx
	popq %rsi
	popq %rdi			#reset variable values
	incq %r11
	jmp loop
endl:
	#cmp $-128, %r9
	#jl overflow
	cmp $127, %r9
	jg overflow
	jmp endof
overflow:
	movq $1, %r10
endof:
	movq %r10, %rdx
	ret


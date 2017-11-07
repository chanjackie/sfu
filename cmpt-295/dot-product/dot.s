
	.globl dot

dot:
	movq	(%rdi), %rax  
	imulq	(%rsi), %rax   # x[0] * y[0]

	pushq	%rax           # spill partial computation
	 
	movq	8(%rdi), %rax  
	imulq	8(%rsi), %rax  # x[1] * y[1]
	 
	addq	(%rsp), %rax   # add x[0]*y[0]
	 
	addq	$8, %rsp	   # pop to nowhere
	# leaq	8(%rsp), %rsp  # Alt: pop to nowhere
	
	ret


	# Alternate:

	movq	(%rdi), %rax  
	imulq	(%rsi), %rax   # x[0] * y[0]
	 
	pushq	%rbx           # save value of rbx
	 
	movq	8(%rdi), %rbx  
	imulq	8(%rsi), %rbx  # x[1] * y[1]
	 
	addq	%rbx, %rax
	 
	popq	%rbx           # restore value of rbx
	 
	ret


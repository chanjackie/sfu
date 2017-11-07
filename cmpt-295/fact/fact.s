
	.globl fact

	# Algorithm:
	#    fact(int n) {
	#       if (n <= 1) return 1;
	#       return n * fact(n-1);
	#    }

	# %rdi : n
fact:
	cmp $1, %rdi
	jg endif
	mov $1, %rax  # if (n <= 1) return 1;
	ret

endif:
	pushq %rdi    # save n
	decq %rdi     # n-1
	call fact     # fact(n-1)
	imulq (%rsp), %rax # n*fact(n-1)
	leaq 8(%rsp), %rsp # recycle
	#popq %rsi

	ret

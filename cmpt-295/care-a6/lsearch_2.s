# Variable Map:
# %rsi: n
# %rdi: A[n] (base pointer)
# %edx: target
# %ecx: i
# %r8d: A[n-1]

	.globl	lsearch_2
lsearch_2:
	testl	%esi, %esi				# if n<=0 {
	jle notfound
	movslq	%esi, %rax
	leaq	-4(%rdi,%rax,4), %rax
	movl	(%rax), %r8d			# tmp = A[n-1]
	movl	%edx, (%rax)			# A[n-1] = target
	cmpl	(%rdi), %edx			# if (A[0] == target) {
	je	equaltarget					
	addq	$4, %rdi
	xorl	%ecx, %ecx				# i = 0
while:								# do {
	addq	$4, %rdi				# 	
	addl	$1, %ecx				#	i++
	cmpl	-4(%rdi), %edx			# } while (A[i]!=target)
	jne	while
endwhile:
	movl	%r8d, (%rax)			# A[n-1] = tmp
	leal	-1(%rsi), %eax			# %eax: n-1
	cmpl	%ecx, %eax				# if (n-1 > i) {
	jg targetfound
	cmpl	%edx, %r8d				# if (A[n-1] != target) {
	jne	notfound
	rep ret							# else return n-1
targetfound:
	movl	%ecx, %eax				# return i
	ret
notfound:
	movl	$-1, %eax				# return -1 (target not found)
	ret
equaltarget:
	xorl	%ecx, %ecx				# i = 0
	jmp	endwhile					

	.globl	sum
sum:
	# jmp version1	
version2:
	mov $0, %eax   # int total = 0;
	mov %esi, %ecx   # for (i = 0; i < n; i++) {

for: add -4(%rdi, %rcx, 4), %eax
	loop for       # }
	
	# return total;
	ret

version1:
	# version 1:
	mov $0, %eax   # int total = 0;
	mov $0, %ecx   # for (i = 0; i < n; i++) {

forloop:
	cmp %esi, %ecx
	jge endloop    #   exit if i >= n

	add (%rdi, %rcx, 4), %eax  # total += A[i];
	inc %ecx
	jmp forloop    # }

endloop:
	# return total;
	ret


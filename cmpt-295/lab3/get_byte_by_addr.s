	.globl get_byte_by_addr
get_byte_by_addr:
	movl $0, %eax   
	
	# place your code for Part 3 here
	movb (%rsi,%rdi), %al
	# end of Part 3

	ret

	.globl sum_float

	# var map:
	#   %xmm0:  total
	#   %rdi:   F[n] (base pointer)
	#   %rsi:   n
	#   %rbp:   endptr

sum_float:
	push	%rbp

	xorps	%xmm0, %xmm0            # total <- 0.0
	leaq	(%rdi, %rsi, 4), %rbp   # endptr <- F + n

loop:
	cmpq	%rdi, %rbp             
	jle	endloop                 # while (F < endptr) {
	addss	(%rdi), %xmm0           #    total += F[0]
	add	$4, %rdi                #    F++
	jmp	loop                    # }

endloop:
	pop	%rbp
	ret


    .globl matrix_prod
matrix_prod:            # void matrix_prod(void *A, void *B, void *C, int n);
    xorl %eax, %eax
    movl $0, %r8d       # i <- 0
    movl $0, %r9d       # j <- 0
loop:
    cmpl %ecx, %r8d
    jge endloop
inloop:
    cmpl %ecx, %r9d     # for (j=0;j<n;j++) {
    jge endin
    pushq %rdx
    movq %rcx, %rdx
    pushq %rcx
    movq %r8, %rcx
    pushq %r8
    movq %r9, %r8
    pushq %r9
    pushq %rdi
    pushq %rsi
    call dot_prod
    popq %rsi
    popq %rdi
    popq %r9
    popq %r8
    popq %rcx
    popq %rdx
    pushq %rdi
    movq %rax, %rdi
    pushq %rsi
    movq $17, %rsi
    pushq %rdx
    call mod
    popq %rdx
    popq %rsi
    popq %rdi
    movq %rax, (%rdx)
    addq $8, %rdx
    incl %r9d
    jmp inloop
endin:
    movl $0, %r9d
    incl %r8d
    jmp loop
endloop:
	ret

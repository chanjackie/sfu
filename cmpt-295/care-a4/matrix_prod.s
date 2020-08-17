
    # var map
    # %r14d - i
    # %r15d - j
    # %rdi - A[N] base pointer
    # %rsi - B[N] base pointer
    # %rdx - C[N] base pointer
    # %rcx - n
    .globl matrix_prod
matrix_prod:            # void matrix_prod(void *A, void *B, void *C, int n);
    xorl %eax, %eax
    pushq %r14
    pushq %r15
    movq $0, %r14      # i <- 0
    movq $0, %r15       # j <- 0
loop:                   
    cmpq %rcx, %r14     # for (i=0;i<n;i++) {
    jge endloop
inloop:
    cmpq %rcx, %r15     # for (j=0;j<n;j++) {
    jge endin
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    movq %rcx, %rdx
    movq %r14, %rcx
    movq %r15, %r8
    call dot_prod
    movq %rax, %rdi
    movq $17, %rsi
    call mod
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    movq %rax, (%rdx)
    incq %rdx
    incq %r15
    jmp inloop
endin:
    movq $0, %r15
    incq %r14
    jmp loop
endloop:
    popq %r15
    popq %r14
	ret

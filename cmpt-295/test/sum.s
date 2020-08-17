.globl sum

sum:
    mov $0, %eax
    mov $0, %ecx
loop:
    cmp %ecx, %esi
    jle endloop
    addl (%edi, %ecx, 8), %eax
    inc %ecx
    jmp loop
endloop:
    ret
